type headerProps;

type navigationParams = Js.Dict.t string;

type navigationPathsConfig = Js.Dict.t string;

type navigationAction;

module Navigation: {
  type t;
  type state = {
    routeName: string,
    key: string,
    params: navigationParams,
    path: option string,
    index: option int,
    routes: option (array state)
  };
  let state: t => state;
  let navigate: t => routeName::string => params::Js.Dict.t string? => unit => unit;
  external setParams : t => Js.Dict.t string => unit = "" [@@bs.send];
  let goBack: t => from::[ | `anywhere | `routeKey string]? => unit => unit;
  external dispatch : t => navigationAction = "" [@@bs.send];
};

type navigation = Navigation.t;

module StackNavigator: {
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
    type configRecord 'style = {
      initialRouteName: option string,
      initialRouteParams: option navigationParams,
      paths: option navigationPathsConfig,
      navigationOptions: option (navigationOptionsRecord 'style),
      mode: option [ | `card | `modal],
      headerMode: option [ | `float | `none | `screen],
      cardStyle: option 'style,
      onTransitionStart: option (unit => unit),
      onTransitionEnd: option (unit => unit)
    };
    type screenBag 'screenProps 'style = {
      navigation: Navigation.t,
      screenProps: 'screenProps,
      navigationOptions: navigationOptionsRecord 'style
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
    initialRouteParams::navigationParams? =>
    paths::navigationPathsConfig? =>
    navigationOptions::navigationOptions 'style? =>
    mode::[< | `card | `modal]? =>
    headerMode::[< | `float | `none | `screen]? =>
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
    dynamicNavigationOptions::
      (
        Component.screenBag 'screenProps 'style =>
        navigationOptions 'style
      )? =>
    unit =>
    routeConfig 'screenProps 'style;
  type routesConfig 'screenProps 'style;
  let routesConfig: list (string, routeConfig 'screenProps 'style) => routesConfig 'screenProps 'style;
  module type StackNavigatorSpec = {
    type props;
    type style;
    let routes: routesConfig props style;
    let config: option (config style);
  };
  module CreateComponent:
    (Spec: StackNavigatorSpec) =>
    {
      let wrapProps:
        'a =>
        children::list ReactRe.reactElement =>
        ref::(ReactRe.reactRef => unit)? =>
        key::string? =>
        unit =>
        ReactRe.reactElement;
    };
};