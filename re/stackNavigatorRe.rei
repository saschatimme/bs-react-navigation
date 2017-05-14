type headerProps;

type style = ReactNative.Style.t;

module Component: {
  type navigationOptionsRecord = {
    title: option string,
    header: option (headerProps => ReactRe.reactElement),
    headerVisible: option bool,
    headerTitle: option ReactRe.reactElement,
    headerTitleStyle: option style,
    headerTintColor: option string,
    headerBackTitle: option string,
    headerTruncatedBackTitle: option string,
    headerLeft: option ReactRe.reactElement,
    headerBackTitleStyle: option style,
    headerPressColorAndroid: option string,
    headerRight: option ReactRe.reactElement,
    headerStyle: option style,
    gesturesEnabled: option bool
  };
  type screenBag 'screenProps = {
    navigation: NavigationRe.t,
    screenProps: 'screenProps,
    navigationOptions: option navigationOptionsRecord
  };
};

type navigationOptions;

let navigationOptions:
  title::string? =>
  header::(headerProps => ReactRe.reactElement)? =>
  headerVisible::bool? =>
  headerTitle::ReactRe.reactElement? =>
  headerTitleStyle::style? =>
  headerTintColor::string? =>
  headerBackTitle::string? =>
  headerTruncatedBackTitle::string? =>
  headerLeft::ReactRe.reactElement? =>
  headerBackTitleStyle::style? =>
  headerPressColorAndroid::string? =>
  headerRight::ReactRe.reactElement? =>
  headerStyle::style? =>
  gesturesEnabled::bool? =>
  unit =>
  navigationOptions;

type config;

let config:
  initialRouteName::string? =>
  initialRouteParams::Js.Dict.t string? =>
  paths::Js.Dict.t string? =>
  navigationOptions::navigationOptions? =>
  mode::[ | `card | `modal]? =>
  headerMode::[ | `float | `none | `screen]? =>
  cardStyle::style? =>
  onTransitionStart::(unit => unit)? =>
  onTransitionEnd::(unit => unit)? =>
  unit =>
  config;

type routeConfig 'screenProps;

let routeConfig:
  screen::(Component.screenBag 'screenProps => ReactRe.reactElement) =>
  path::string? =>
  navigationOptions::navigationOptions? =>
  dynamicNavigationOptions::(Component.screenBag 'screenProps => navigationOptions)? =>
  unit =>
  routeConfig 'screenProps;

type routesConfig 'screenProps;

let routesConfig: list (string, routeConfig 'screenProps) => routesConfig 'screenProps;

module type StackNavigatorSpec = {
  type screenProps;
  let routes: routesConfig screenProps;
  let config: option config;
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