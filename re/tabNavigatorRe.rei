module Component: {
  type navigationOptionsRecord = {title: option string, tabBarVisible: option bool};
  type screenBag 'screenProps = {
    navigation: NavigationRe.t,
    screenProps: 'screenProps,
    navigationOptions: option navigationOptionsRecord
  };
};

type navigationOptions;

let navigationOptions:
  title::string? =>
  tabBarVisible::bool? =>
  tabBarIcon::(focused::bool => tintColor::string => ReactRe.reactElement)? =>
  tabBarLabel::(focused::bool => tintColor::string => ReactRe.reactElement)? =>
  unit =>
  navigationOptions;


type tabBarOptions 'style;

let tabBarOptions:
  activeTintColor::string? =>
  activeBackgroundColor::string? =>
  inactiveTintColor::string? =>
  inactiveBackgroundColor::string? =>
  showLabel::bool? =>
  style::'style? =>
  labelStyle::'style? =>
  showIcon::bool? =>
  upperCaseLabel::bool? =>
  pressColor::bool? =>
  pressOpacity::float? =>
  scrollEnabled::bool? =>
  tabStyle::'style? =>
  indicatorStyle::'style? =>
  iconStyle::'style? =>
  unit =>
  tabBarOptions 'style;

type config 'style;

let config:
  tabBarOptions::tabBarOptions 'style? =>
  animationEnabled::bool? =>
  backBehavior::[< | `initialRoute | `none]? =>
  lazy_::bool? =>
  order::array string? =>
  swipeEnabled::bool? =>
  tabBarPosition::[< | `bottom | `top]? =>
  initialRouteName::string? =>
  paths::Js.Dict.t string? =>
  tabBarComponent::ReactRe.reactClass? =>
  unit =>
  config 'style;



type routeConfig 'screenProps;

let routeConfig:
  screen::(Component.screenBag 'screenProps => ReactRe.reactElement) =>
  path::string? =>
  navigationOptions::navigationOptions? =>
  dynamicNavigationOptions::( Component.screenBag 'screenProps => navigationOptions)? =>
  unit =>
  routeConfig 'screenProps;

type routesConfig 'screenProps;

let routesConfig: list (string, routeConfig 'screenProps) => routesConfig 'screenProps;

module type TabNavigatorSpec = {
  type screenProps;
  type style;
  let routes: routesConfig screenProps;
  let config: option (config 'style);
};

module CreateComponent:
  (Spec: TabNavigatorSpec) =>
  {
    let wrapProps:
      Spec.screenProps =>
      children::list ReactRe.reactElement =>
      ref::(ReactRe.reactRef => unit)? =>
      key::string? =>
      unit =>
      ReactRe.reactElement;
  };

