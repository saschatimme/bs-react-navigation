open ReactNative;

open ReactNavigation;

module SimpleStack = {
  include StackNavigator.Component;
  type screenProps = unit;
  let params name::(name: string) => {
    let dict = Js.Dict.empty ();
    Js.Dict.set dict "name" name;
    dict
  };
  let myNavScreen navigation::(navigation: Navigation.t) banner::(banner: string) =>
    <ScrollView>
      <SampleText value=banner />
      <Button
        onPress=(
                  fun () =>
                    Navigation.navigate
                      navigation routeName::"Profile" params::(params name::"Jane") ()
                )
        title="Go to a profile screen"
      />
      <Button
        onPress=(
                  fun () =>
                    Navigation.navigate
                      navigation routeName::"Photos" params::(params name::"Jane") ()
                )
        title="Go to a photos screen"
      />
    </ScrollView>;
  let myHomeScreen {navigation} => myNavScreen ::navigation banner::"Home screen";
  let myPhotosScreen {navigation} => {
    let state = Navigation.state navigation;
    let name = Js.Dict.unsafeGet state.params "name";
    myNavScreen ::navigation banner::{j|$(name)'s Photos|j}
  };
  let myProfileScreen {navigation} => {
    let state = Navigation.state navigation;
    let editStatus =
      switch (Js.Dict.get state.params "mode") {
      | Some "edit" => "Now Editing "
      | _ => ""
      };
    /*
         Long / Safe way
         let name =
         switch (Js.Dict.get state.params "name") {
         | Some name => name
         | None => "Unknown"
     };*/
    /*  Yolo way */
    let name = Js.Dict.unsafeGet state.params "name";
    myNavScreen ::navigation banner::{j|$(editStatus)$(name)'s Profile|j}
  };
  let routes =
    StackNavigator.(
      routesConfig [
        (
          "Home",
          routeConfig
            screen::myHomeScreen navigationOptions::(navigationOptions title::"Welcome" ()) ()
        ),
        (
          "Photos",
          routeConfig
            screen::myPhotosScreen
            path::"photos/:name"
            navigationOptions::(navigationOptions title::"Photos" ())
            ()
        ),
        (
          "Profile",
          {
            let screen = myProfileScreen;
            let dynamicNavigationOptions {navigation} => {
              let state = Navigation.state navigation;
              /*
                   Long / Safe way
                   let name =
                   switch (Js.Dict.get state.params "name") {
                   | Some name => name
                   | None => "Unknown"
               };*/
              /*  Yolo way */
              let name = Js.Dict.unsafeGet state.params "name";
              let isEditing =
                switch (Js.Dict.get state.params "mode") {
                | Some "edit" => true
                | _ => false
                };
              let title = if isEditing {"Done"} else {"Edit"};
              let onPress () => {
                let mode =
                  switch (Js.Dict.get state.params "mode") {
                  | Some "edit" => ""
                  | _ => "edit"
                  };
                let params = Js.Dict.empty ();
                Js.Dict.set params "mode" mode;
                Navigation.setParams navigation params
              };
              let headerRight = <Button title onPress />;
              navigationOptions
                headerTitle::(ReactRe.stringToElement {j|$(name)'s Profile|j}) ::headerRight ()
            };
            routeConfig ::screen path::"people/:name" ::dynamicNavigationOptions ()
          }
        )
      ]
    );
  let config = None;
};

include StackNavigator.CreateComponent SimpleStack;

let createElement = wrapProps ();