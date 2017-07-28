/*open ReactNative;

open ReactNavigation;

include TabNavigator.Component;

/* TODO Upstream to bs-react-native */
let isPlatform (os: Platform.os) =>
  switch (os, Platform.os ()) {
  | (IOS, IOS) => true
  | (Android, Android) => true
  | _ => false
  };

let styles =
  StyleSheet.create {
    "container":
      Style.(
        style [
          marginTop (
            if (isPlatform Platform.IOS) {
              20.
            } else {
              0.
            }
          )
        ]
      )
  };

module SimpleTab = {
  type screenProps = unit;
  let myNavScreen ::navigation ::banner =>
    <ScrollView style=styles##container>
      <SampleText value=banner />
      <Button
        onPress=(fun () => Navigation.navigate navigation routeName::"Home" ())
        title="Go to home tab"
      />
      <Button
        onPress=(fun () => Navigation.navigate navigation routeName::"Settings" ())
        title="Go to settings tab"
      />
      <Button
        onPress=(fun () => Navigation.goBack navigation from::`anywhere ())
        title="Go back"
      />
    </ScrollView>;
  let myHomeScreen {navigation} => myNavScreen banner::"Home Tab" ::navigation;
  let myPeopleScreen {navigation} => myNavScreen banner::"People Tab" ::navigation;
  let myChatScreen {navigation} => myNavScreen banner::"Chat Tab" ::navigation;
  let mySettingsScreen {navigation} => myNavScreen banner::"Settings Tab" ::navigation;
  let routes =
    TabNavigator.(
      routesConfig [
        (
          "Home",
          {
            let screen = myHomeScreen;
            let navigationOptions =
              TabNavigator.navigationOptions
                tabBarLabel::(`static (ReactRe.stringToElement "Home"))
                tabBarIcon::(
                  `dynamic (
                    fun ::focused ::tintColor => {
                      let name = if focused {"ios-home"} else {"ios-home-outline"};
                      <Ionicons name size=26 style=Style.(style [color tintColor]) />
                    }
                  )
                )
                ();
            routeConfig ::screen ::navigationOptions ()
          }
        ),
        (
          "People",
          {
            let screen = myPeopleScreen;
            let navigationOptions =
              TabNavigator.navigationOptions
                tabBarLabel::(`static (ReactRe.stringToElement "People"))
                tabBarIcon::(
                  `dynamic (
                    fun ::focused ::tintColor => {
                      let name = if focused {"ios-people"} else {"ios-people-outline"};
                      <Ionicons name size=26 style=Style.(style [color tintColor]) />
                    }
                  )
                )
                ();
            routeConfig ::screen ::navigationOptions ()
          }
        ),
        (
          "Chat",
          {
            let screen = myChatScreen;
            let navigationOptions =
              TabNavigator.navigationOptions
                tabBarLabel::(`static (ReactRe.stringToElement "Chat"))
                tabBarIcon::(
                  `dynamic (
                    fun ::focused ::tintColor => {
                      let name = if focused {"ios-chatboxes"} else {"ios-chatboxes-outline"};
                      <Ionicons name size=26 style=Style.(style [color tintColor]) />
                    }
                  )
                )
                ();
            routeConfig ::screen ::navigationOptions ()
          }
        ),
        (
          "Settings",
          {
            let screen = mySettingsScreen;
            let navigationOptions =
              TabNavigator.navigationOptions
                tabBarLabel::(`static (ReactRe.stringToElement "Settings"))
                tabBarIcon::(
                  `dynamic (
                    fun ::focused ::tintColor => {
                      let name = if focused {"ios-settings"} else {"ios-settings-outline"};
                      <Ionicons name size=26 style=Style.(style [color tintColor]) />
                    }
                  )
                )
                ();
            routeConfig ::screen ::navigationOptions ()
          }
        )
      ]
    ); 
  let activeTintColor =
    if (isPlatform (Platform.os ())) {
      "#e91e63"
    } else {
      "#fff"
    };
  let config = Some (TabNavigator.config tabBarOptions::(TabNavigator.tabBarOptions ::activeTintColor ()) ());
};

include TabNavigator.CreateComponent SimpleTab; 

let createElement = wrapProps ();*/