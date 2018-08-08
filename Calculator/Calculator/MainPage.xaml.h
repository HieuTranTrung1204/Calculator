//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

#include <string>
#include <stdarg.h>
#include <stdio.h>

#include "resource.h"

namespace Calculator
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void btnNumber_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void btnOperator_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void btnAction_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		std::string dataCacul, dataOperat;
		int click = 0;
		double a, b;

		// FEATURES
		void btnFeatures_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		// CURSOR
		::Windows::UI::Core::CoreCursor^ m_cursor;

		// TOAST
		::Windows::UI::Notifications::ToastNotifier^ m_rToastManager;
		::Windows::UI::Notifications::TileUpdater^ m_rTileNotificationUpdater;

		void ShowToast(int timeDelay = 0);
		void ShowTile(int timeExp = 0);
	};
}
