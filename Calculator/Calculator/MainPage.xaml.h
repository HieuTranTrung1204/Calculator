//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

#include <string>
#include <stdarg.h>
#include <stdio.h>

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
		
		std::string dataCacul, dataOperat;
		int click = 0;
		double a, b;
	};
}
