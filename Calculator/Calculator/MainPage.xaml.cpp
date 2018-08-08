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
	m_cursor = ref new Windows::UI::Core::CoreCursor(Windows::UI::Core::CoreCursorType::Custom, IDC_CURSOR2);
	::Windows::UI::Xaml::Window::Current->CoreWindow->GetForCurrentThread()->PointerCursor = m_cursor;
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
