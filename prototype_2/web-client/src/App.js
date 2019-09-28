import React from 'react';
import CssBaseline from '@material-ui/core/CssBaseline';
import Notification from './Notification';
import './App.css';
import 'typeface-roboto';
import { Redirect, Route, Switch } from "react-router-dom";
import Grid from '@material-ui/core/Grid';
import Lock, { fakeAuth } from "./Lock";
import Navbar from './Navbar.js';
import MediaCard from './MediaCard.js';

class App extends React.Component {
  render() {

    return (
      <div className="App">
        <React.Fragment>
          <CssBaseline />
          <meta
            name="viewport"
            content="minimum-scale=1, initial-scale=1, width=device-width, shrink-to-fit=no"
          />
          <Grid
          container
          spacing={16}
          className="App"
          direction="row"
          justify="center"
          alignItems="flex-start">
            <Grid item xs={12}>
              <Grid key="nav" item>
                <Navbar></Navbar>
              </Grid>
              <Grid key="switch" item>
                <Switch>
                  <Route path="/lock" component={Lock} />
                  <Route exact path="/" component={Home} />
                  <PrivateRoute path="/admin" component={Admin} />
                </Switch>
              </Grid>
              <Grid key="not" item>
                <Notification></Notification>
              </Grid>
            </Grid>
          </Grid>
        </React.Fragment>
      </div>
    );
  }
}

//Private router function
const PrivateRoute = ({ component: Component, ...rest }) => {
  return (
    <Route
      {...rest}
      render={props =>
        fakeAuth.isAuthenticated === true ? (
          <Component {...props} />
        ) : (
            <Redirect
              to={{ pathname: "/lock", state: { from: props.location } }}
            />
          )}
    />
  );
};

//Home component
const Home = props => (
  <div>
    <h2>Home {console.log(props)}</h2>
    <MediaCard></MediaCard>
  </div>
);

//Admin component
const Admin = ({ match }) => {
  return (
    <div>
      {" "}
      <h2>Welcome home! </h2>
    </div>
  );
};

export default App;