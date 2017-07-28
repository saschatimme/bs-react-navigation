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
        "header":
          style [
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

type example 'a = {
  name: string,
  description: string,
  screen: 'a => ReasonReact.reactElement
};

let examples () => [|
  (
    "SimpleStack",
    {
      name: "Stack Example",
      description: "A card stack",
      screen: fun _ => ReasonReact.element (SimpleStack.stackRouter screenProps::() [||])
    }
  )
|];

let mainScreen {StackNavigator.navigation: navigation} =>
  <ScrollView>
    <View style=Style.(style [marginTop 20.]) />
    <View style=styles##header>
      <Text style=styles##title>
        (ReasonReact.stringToElement "React Navigation powered by Reason")
      </Text>
    </View>
    (
      Array.map
        (
          fun (routeName, {name, description}) =>
            <TouchableOpacity
              key=routeName onPress=(fun () => Navigation.navigate navigation ::routeName ())>
              <View style=styles##item>
                <Text style=styles##title> (ReasonReact.stringToElement name) </Text>
                <Text style=styles##description> (ReasonReact.stringToElement description) </Text>
              </View>
            </TouchableOpacity>
        )
        (examples ()) |> ReasonReact.arrayToElement
    )
  </ScrollView>;

let exampleRoutes () =>
  Array.map (fun (routeName, {screen}) => (routeName, StackNavigator.route ::screen ())) (examples ()) |> Array.to_list;

let config =
  Some (StackNavigator.config initialRouteName::"Index" headerMode::`none () mode::`modal);

let navigator =
  StackNavigator.create
    StackNavigator.(routes [("Index", route screen::mainScreen ()), ...exampleRoutes ()]) config;

let make children => navigator screenProps::() children;