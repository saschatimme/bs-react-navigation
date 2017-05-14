type headerProps;

module Component: {
  type navigationOptionsRecord 'style = {
    title: option string,
    header: option (headerProps => ReactRe.reactElement),
    headerVisible: option bool,
    headerTitle: option ReactRe.reactElement,
    headerTitleStyle: option 'style,
    headerTintColor: option string,
    headerBackTitle: option string,
    headerTruncatedBackTitle: option string,
    headerLeft: option ReactRe.reactElement,
    headerBackTitleStyle: option 'style,
    headerPressColorAndroid: option string,
    headerRight: option ReactRe.reactElement,
    headerStyle: option 'style,
    gesturesEnabled: option bool
  };
  type screenBag 'screenProps 'style = {
    navigation: NavigationRe.t,
    screenProps: 'screenProps,
    navigationOptions: option (navigationOptionsRecord 'style)
  };
};

type navigationOptions 'style;

let navigationOptions:
  title::string? =>
  header::(headerProps => ReactRe.reactElement)? =>
  headerVisible::bool? =>
  headerTitle::ReactRe.reactElement? =>
  headerTitleStyle::'style? =>
  headerTintColor::string? =>
  headerBackTitle::string? =>
  headerTruncatedBackTitle::string? =>
  headerLeft::ReactRe.reactElement? =>
  headerBackTitleStyle::'style? =>
  headerPressColorAndroid::string? =>
  headerRight::ReactRe.reactElement? =>
  headerStyle::'style? =>
  gesturesEnabled::bool? =>
  unit =>
  navigationOptions 'style;

type config 'style;

let config:
  initialRouteName::string? =>
  initialRouteParams::Js.Dict.t string? =>
  paths::Js.Dict.t string? =>
  navigationOptions::navigationOptions 'style? =>
  mode::[ | `card | `modal]? =>
  headerMode::[ | `float | `none | `screen]? =>
  cardStyle::'style? =>
  onTransitionStart::(unit => unit)? =>
  onTransitionEnd::(unit => unit)? =>
  unit =>
  config 'style;

type routeConfig 'screenProps 'style;

let routeConfig:
  screen::(Component.screenBag 'screenProps 'style => ReactRe.reactElement) =>
  path::string? =>
  navigationOptions::navigationOptions 'style? =>
  dynamicNavigationOptions::(Component.screenBag 'screenProps 'style => navigationOptions 'style)? =>
  unit =>
  routeConfig 'screenProps 'style;

type routesConfig 'screenProps 'style;

let routesConfig:
  list (string, routeConfig 'screenProps 'style) => routesConfig 'screenProps 'style;

module type StackNavigatorSpec = {
  type screenProps;
  type style;
  let routes: routesConfig screenProps style;
  let config: option (config style);
};

module CreateComponent:
  (Spec: StackNavigatorSpec) =>
  {
    let wrapProps:
      Spec.screenProps =>
      children::list ReactRe.reactElement =>
      ref::(ReactRe.reactRef => unit)? =>
      key::string? =>
      unit =>
      ReactRe.reactElement;
  };