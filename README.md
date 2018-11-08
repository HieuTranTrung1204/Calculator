# Part 1: UWP basic

## * Style
- <https://docs.microsoft.com/en-us/windows/uwp/design/controls-and-patterns/xaml-styles> 
- <https://docs.microsoft.com/en-us/windows/uwp/design/basics/xaml-basics-style> 

## * Toast notificaiton
add lib
  ```
    Microsoft.Toolkit.Uwp.Notifications
    QueryString.NET
  ```
using lib:
  ```
    using Windows.UI.Notifications;
    using Microsoft.Toolkit.Uwp.Notifications; // Notifications library
    using Microsoft.QueryStringDotNET; // QueryString.NET
  ```

## * Tiles
- https://docs.microsoft.com/en-us/windows/uwp/design/shell/tiles-and-notifications/creating-tiles 

## * Asset 
  import to folder Assets
    ```
      "ms-appx:///Assets/GL_Logo.png"
    ```

##  * Custom pointer cursor
  - Project C#: <https://docs.microsoft.com/en-us/uwp/api/windows.ui.core.corecursor>
  - Project C++: <https://social.msdn.microsoft.com/Forums/en-US/14001796-bcd5-4b9d-9d7e-13bc6ba59d2d/uwp-how-to-set-a-pointer-cursor-as-a-circle-instead-of-a-window-default-cursor?forum=wpdevelop>
  
  We need just proper ".res " file, For that we should do following 
  
    
    1) Create any C++ project.  For example dll,  Add new C++ Dll project name it for example as ResourcesComponent.
    
    2) Add a resource file to the project. [right-mouse] the project name "ResourcesComponent" => Add New Item => Visual C++ => Resource File (.rc)
    
    3) Name the resource file for example "Resources.rc"
    
    4) Add a cursor resource.  Double click on "Resources.rc" the it will open in  Resource View tab then Right click  on "Resources.rc" => Add Resource => Cursor => New (Here you can modify cursor appearance by pen)
    
    5) Go back to solution explorer and now you will see resource.h file where you can find its id  
      #define IDC_CURSOR1                     101
    6) Build dll in Release mode 
    
    7) In Release sub folder you can find Resource.res file 
    
    Now we have proper .res file,  We should add it to our UWP project.
    
    1) Copy Resource.res file  to UWP project directory. (You can delete DLL project as it is no longer needed ) 
    
    2) Unload UWP project in VS.
    
    3) Rigth click on unloaded project and select edit .csproj 
    
    4) in first PropertyGroup (where is Appname, TargetPlatform, etc ) add
        <ItemGroup>
          <ResourceCompile Include="Resource.rc" />
        </ItemGroup>   
    5) Reload project 
    
    6) Use following code for set cursor in your image PointerEnter event handler 
        m_cursor = ref new Windows::UI::Core::CoreCursor(Windows::UI::Core::CoreCursorType::Custom, IDC_CURSOR1);
      ::Windows::UI::Xaml::Window::Current->CoreWindow->GetForCurrentThread()->PointerCursor = m_cursor;

## * GameDemo
- <https://code.msdn.microsoft.com/windowsapps/Tic-Tac-Toe-in-Windows-10-d50a7a27/sourcecode?fileId=146059&pathId=660827241>
- <https://corina.microsoft.pub.ro/2016/08/27/how-to-create-a-simple-game-using-universal-windows-platform/>  

-----------------------------------------------
# Part 2: Game với UWP 
## * WCP
-
