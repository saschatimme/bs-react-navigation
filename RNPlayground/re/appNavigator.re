open ReactNative;

open ReactNavigation;

let styles =
  StyleSheet.create
    Style.(
      {
        "item":
          style [
            backgroundColor "#fff",
            paddingHorizontal 16.,
            paddingVertical 12.,
            borderBottomWidth StyleSheet.hairlineWidth,
            borderBottomColor "#ddd"
          ],
        "title": style [fontSize 16., fontWeight `bold, color "#444"],
        "header": style [
            backgroundColor "#fff",
            paddingHorizontal 16.,
            paddingVertical 12.,
            borderBottomWidth StyleSheet.hairlineWidth,
            borderBottomColor "#ddd",
            margin 12.
          ],
        "description": style [fontSize 13., color "#999"]
      }
    );

type example 'a = {name: string, description: string, screen: 'a => ReactRe.reactElement};

let exampleList = [
  (
    "SimpleStack",
    {name: "Stack Example", description: "A card stack", screen: fun _ => <SimpleStack />}
  ),
  (
    "SimpleTabs",
    {
      name: "Tabs Example",
      description: "Tabs following platform conventions",
      screen: fun _ => <SimpleTab />
    }
  )
];

module App = {
  include StackNavigator.Component;
  type screenProps =
    | ();
  let mainScreen {navigation} =>
    <ScrollView>
      <View style=Style.(style [marginTop 20.]) />
      <View style=styles##header>
        <Text style=styles##title> (ReactRe.stringToElement "React Navigation powered by Reason") </Text>
      </View>
      (
        List.map
          (
            fun (routeName, {name, description}) =>
              <TouchableOpacity
                key=routeName onPress=(fun () => Navigation.navigate navigation ::routeName ())>
                <View style=styles##item>
                  <Text style=styles##title> (ReactRe.stringToElement name) </Text>
                  <Text style=styles##description> (ReactRe.stringToElement description) </Text>
                </View>
              </TouchableOpacity>
          )
          exampleList |> ReactRe.listToElement
      )
    </ScrollView>;
  let exampleRoutes =
    List.map
      (fun (routeName, {screen}) => (routeName, StackNavigator.routeConfig ::screen ()))
      exampleList;
  let routes =
    StackNavigator.(routesConfig [("Index", routeConfig screen::mainScreen ()), ...exampleRoutes]);
  let config = Some (StackNavigator.config initialRouteName::"Index" headerMode::`none () mode::`modal);
};

include StackNavigator.CreateComponent App;

let createElement = wrapProps ();