# Toast
----------------------------------
## ShowToastNotification
```
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

```
----------------------------------

## ShowToastNotificationScheduled
  ```
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
  ``` 
  
 ----------------------------------