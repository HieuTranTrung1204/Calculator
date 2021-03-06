﻿using Microsoft.QueryStringDotNET;
using Microsoft.Toolkit.Uwp.Notifications;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Data.Xml.Dom;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Notifications;
using Windows.UI.StartScreen;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace UWPFeatures
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }
        void ShowToastNotificationScheduled(int timeDelay)
        {
            string xml = @"<toast>
                                <visual>
                                <binding template=""ToastGeneric"">
                                    <text>Hello!</text>
                                    <text>This is a scheduled toast!</text>
                                </binding>
                                </visual>
                            </toast>";

            XmlDocument doc = new XmlDocument();
            doc.LoadXml(xml);

            ScheduledToastNotification toast = new ScheduledToastNotification(doc, DateTimeOffset.Now.AddSeconds(timeDelay));
            ToastNotificationManager.CreateToastNotifier().AddToSchedule(toast);
        }
        void ShowToastXml()
        {
            // template to load for showing Toast Notification
            var xmlToastTemplate = "<toast launch=\"app-defined-string\">" +
                                     "<visual>" +
                                       "<binding template =\"ToastGeneric\">" +
                                         "<text>Sample Notification</text>" +
                                         "<text>" +
                                           "This is a sample toast notification from Hieu" +
                                         "</text>" +
                                       "</binding>" +
                                     "</visual>" +
                                   "</toast>";

            // load the template as XML document
            var xmlDocument = new XmlDocument();
            xmlDocument.LoadXml(xmlToastTemplate);

            // create the toast notification and show to user
            var toastNotification = new ToastNotification(xmlDocument);
            var notification = ToastNotificationManager.CreateToastNotifier();
            notification.Show(toastNotification);
        }
        void ShowToastNotification()
        {
            // In a real app, these would be initialized with actual data
            string title = "Title notificaiton sent you a picture";
            string content = "Check this out, Happy Coding!";
            string image = "http://p6i771owklq1zv0eh1wqu4n1-wpengine.netdna-ssl.com/wp-content/uploads/2016/01/Gameloft-Gets-With-AppNexus-What-Are-They-Up-To-300x229.png";
            string logo = "ms-appdata:///local/menu.jpg";
            int conversationId = 384928;

            // Construct the visuals of the toast
            ToastVisual visual = new ToastVisual()
            {
                BindingGeneric = new ToastBindingGeneric()
                {
                    Children =
                    {
                        new AdaptiveText()
                        {
                            Text = title
                        },

                        new AdaptiveText()
                        {
                            Text = content
                        },

                        new AdaptiveImage()
                        {
                            Source = image
                        }
                    },

                    AppLogoOverride = new ToastGenericAppLogo()
                    {
                        Source = logo,
                        HintCrop = ToastGenericAppLogoCrop.Circle
                    }
                }
            };

            // Construct the actions for the toast (inputs and buttons)
            ToastActionsCustom actions = new ToastActionsCustom()
            {
                Inputs =
                {
                    new ToastTextBox("tbReply")
                    {
                        PlaceholderContent = "Type a response"
                    }
                },

                Buttons =
                {
                    new ToastButton("Reply", new QueryString()
                    {
                        { "action", "reply" },
                        { "conversationId", conversationId.ToString() }

                    }.ToString())
                    {
                        ActivationType = ToastActivationType.Background,
                        ImageUri = "Assets/Reply.png",

                        // Reference the text box's ID in order to
                        // place this button next to the text box
                        TextBoxId = "tbReply"
                    },

                    new ToastButton("Like", new QueryString()
                    {
                        { "action", "like" },
                        { "conversationId", conversationId.ToString() }

                    }.ToString())
                    {
                        ActivationType = ToastActivationType.Background
                    },

                    new ToastButton("View", new QueryString()
                    {
                        { "action", "viewImage" },
                        { "imageUrl", image }

                    }.ToString())
                }
            };


            // Now we can construct the final toast content
            ToastContent toastContent = new ToastContent()
            {
                Visual = visual,
                Actions = actions,

                // Arguments when the user taps body of toast
                Launch = new QueryString()
                {
                    { "action", "viewConversation" },
                    { "conversationId", conversationId.ToString() }

                }.ToString()
            };

            // And create the toast notification
            ToastNotification notification = new ToastNotification(toastContent.GetXml());
            // And then send the toast
            ToastNotificationManager.CreateToastNotifier().Show(notification);        
        }

        // Tiles
        void ShowTiles()
        {
            // In a real app, these would be initialized with actual data
            string from = "text 1";
            string subject = "texxt 2";
            string body = "detail ";


            // Construct the tile content
            TileContent content = new TileContent()
            {
                Visual = new TileVisual()
                {
                    TileMedium = new TileBinding()
                    {
                        Content = new TileBindingContentAdaptive()
                        {
                            Children =
                {
                    new AdaptiveText()
                    {
                        Text = from
                    },

                    new AdaptiveText()
                    {
                        Text = subject,
                        HintStyle = AdaptiveTextStyle.CaptionSubtle
                    },

                    new AdaptiveText()
                    {
                        Text = body,
                        HintStyle = AdaptiveTextStyle.CaptionSubtle
                    }
                }
                        }
                    },

                    TileWide = new TileBinding()
                    {
                        Content = new TileBindingContentAdaptive()
                        {
                            Children =
                {
                    new AdaptiveText()
                    {
                        Text = from,
                        HintStyle = AdaptiveTextStyle.Subtitle
                    },

                    new AdaptiveText()
                    {
                        Text = subject,
                        HintStyle = AdaptiveTextStyle.CaptionSubtle
                    },

                    new AdaptiveText()
                    {
                        Text = body,
                        HintStyle = AdaptiveTextStyle.CaptionSubtle
                    }
                }
                        }
                    }
                }
            };
            // Create the tile notification
            var tileNotification = new TileNotification(content.GetXml());
            tileNotification.ExpirationTime = DateTimeOffset.UtcNow.AddSeconds(5);
            
            // Send the notification to the primary tile
            TileUpdateManager.CreateTileUpdaterForApplication().Update(tileNotification);
        }
        private void btnShowToastSched_Click(object sender, RoutedEventArgs e)
        {
            //ShowToastNotificationScheduled(3);
        }

        private void btnShowToast_Click(object sender, RoutedEventArgs e)
        {
            //ShowToastNotification();

            // SecondaryTile secondaryTile = new SecondaryTile("");
            // secondaryTile.VisualElements.Square150x150Logo = new Uri("ms-appx:///Assets/Square44x44Logo.scale-100.png");
            //secondaryTile.UpdateAsync();

            //ShowToastXml();

            ShowTiles();
        }
    }
}
