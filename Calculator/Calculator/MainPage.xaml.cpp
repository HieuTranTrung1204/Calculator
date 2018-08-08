//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Calculator;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

template <typename T>
std::string to_string(T const& value) {
	stringstream sstr;
	sstr << value;
	return sstr.str();
}

Platform::String^ convertFromString(std::string& input)
{
	std::wstring w_str = std::wstring(input.begin(), input.end());
	const wchar_t* w_chars = w_str.c_str();

	return (ref new Platform::String(w_chars));
}
std::string convertToStdString(Platform::String ^input)
{
	std::wstring fooW(input->Begin());
	std::string fooA(fooW.begin(), fooW.end());

	return fooA;
}
double convertToDouble(Platform::String^ input)
{
	wchar_t* end;
	double result = std::wcstod(input->Data(), &end);

	return result;
}

//std::string format(const std::string fmt_str, ...)
//{
//	va_list ap;
//	char *fp = NULL;
//	va_start(ap, fmt_str);
//	vasprintf(&fp, fmt_str.c_str(), ap);
//	va_end(ap);
//	std::unique_ptr<char[]> formatted(fp);
//	return std::string(formatted.get());
//}

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	// CURSOR
	m_cursor = ref new Windows::UI::Core::CoreCursor(Windows::UI::Core::CoreCursorType::Custom, IDC_CURSOR2);
	::Windows::UI::Xaml::Window::Current->CoreWindow->GetForCurrentThread()->PointerCursor = m_cursor;

	m_rToastManager = ::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier();
	m_rTileNotificationUpdater = ::Windows::UI::Notifications::TileUpdateManager::CreateTileUpdaterForApplication();
	
}

// TOAST
void Calculator::MainPage::ShowToast(int timeDelay)
{
	::Windows::UI::Notifications::ToastTemplateType _ToastTemplate;
	_ToastTemplate = ::Windows::UI::Notifications::ToastTemplateType::ToastImageAndText02;
	::Windows::Data::Xml::Dom::XmlDocument^ _rToastXml = ::Windows::UI::Notifications::ToastNotificationManager::GetTemplateContent(_ToastTemplate);

	// Add Text 
	const wchar_t* i_aTitleText = L"Tieu de";
	const wchar_t* i_aBodyText = L"body";
	::Windows::Data::Xml::Dom::XmlNodeList^ _rToastTextElements = _rToastXml->GetElementsByTagName("text");
	_rToastTextElements->Item(0)->InnerText = ref new ::Platform::String(i_aTitleText);
	_rToastTextElements->Item(1)->InnerText = ref new ::Platform::String(i_aBodyText);


	if (timeDelay > 0)
	{
		::Windows::Globalization::Calendar _Cl;
		_Cl.SetToNow();
		_Cl.AddSeconds(timeDelay);
		::Windows::Foundation::DateTime _StartTime = _Cl.GetDateTime();
		::Windows::UI::Notifications::ScheduledToastNotification^ _rToast = ref new ::Windows::UI::Notifications::ScheduledToastNotification(_rToastXml, _StartTime);

		m_rToastManager->AddToSchedule(_rToast);
	}
	else
	{
		::Windows::UI::Notifications::ToastNotification^ _rToast = ref new ::Windows::UI::Notifications::ToastNotification(_rToastXml);
		m_rToastManager->Show(_rToast);
	}

}

// TILE
void Calculator::MainPage::ShowTile(int timeExp)
{
	::Windows::UI::Notifications::TileTemplateType _TileTemplate;
	_TileTemplate = ::Windows::UI::Notifications::TileTemplateType::TileSquare150x150Text02;
	::Windows::Data::Xml::Dom::XmlDocument^ _rTileXml = ::Windows::UI::Notifications::TileUpdateManager::GetTemplateContent(_TileTemplate);

	const wchar_t* i_aTitleText = L"Tieu de";
	const wchar_t* i_aBodyText = L"body";
	::Windows::Data::Xml::Dom::XmlNodeList^ _rToastTextElements = _rTileXml->GetElementsByTagName("text");
	_rToastTextElements->Item(0)->InnerText = ref new ::Platform::String(i_aTitleText);
	_rToastTextElements->Item(1)->InnerText = ref new ::Platform::String(i_aBodyText);
	
	::Windows::UI::Notifications::TileNotification^ rTile = ref new ::Windows::UI::Notifications::TileNotification(_rTileXml);
	m_rTileNotificationUpdater->Update(rTile);
}


void Calculator::MainPage::btnOperator_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	

	String^ operat = ((Button^)sender)->Content->ToString();
	if (operat->Equals(L"="))
	{
		if (click == 1)
		{
			b = std::atoi(dataCacul.c_str());
		}

		if (dataOperat.compare("+") == 0)
		{
			dataCacul = std::to_string(a + b);
		}
		else if (dataOperat.compare("-") == 0)
		{
			dataCacul = std::to_string(a - b);
		}
		else if (dataOperat.compare("x") == 0)
		{
			dataCacul = std::to_string(a * b);
		}
		else if (dataOperat.compare("/") == 0)
		{
			dataCacul = std::to_string(a / b);
		}

		txtText->Text = convertFromString(dataCacul);
		click = 0;
		dataCacul.clear();
	}
	else
	{
		if (click == 0)
		{
			a = std::atoi(dataCacul.c_str());
		}
		click++;
		dataOperat = convertToStdString(operat);
	}
}

void Calculator::MainPage::btnNumber_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (click == 1)
	{
		dataCacul.clear();
	}

	String^ number = ((Button^)sender)->Content->ToString();
	dataCacul.append(convertToStdString(number));

	txtText->Text = convertFromString(dataCacul);
}

void Calculator::MainPage::btnAction_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	String^ action = ((Button^)sender)->Content->ToString();
	if (action->Equals(L"C"))
	{
		dataCacul.clear();
		txtText->Text = convertFromString(dataCacul);
	}
}

void  Calculator::MainPage::btnFeatures_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ShowToast(3);
	ShowTile(3);
}