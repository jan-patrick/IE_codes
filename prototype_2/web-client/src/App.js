import React from 'react';
import CssBaseline from '@material-ui/core/CssBaseline';
import Notification from './Notification';
import './App.css';
import 'typeface-roboto';
import { Route, Switch } from "react-router-dom";
import Grid from '@material-ui/core/Grid';
import Lock from "./Lock";
import Unlocked from "./Unlocked";
import homescreen from './homescreen.jpg';

const divStyle = {
  width: '412px',
  height: '740px',
  backgroundImage: `url(${homescreen})`,
  backgroundSize: 'cover'
};

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
              <Grid key="switch" item>
                <Switch>
                  <Route path="/lock" component={Lock} />
                  <Route path="/unlocked" component={Unlocked} />
                  <Route exact path="/" component={Home} />
                </Switch>
              </Grid>
            </Grid>
          </Grid>
        </React.Fragment>
      </div>
    );
  }
}

//Home component
const Home = props => (
  <div className="home" style={divStyle} >
    <Notification></Notification>
  </div>
);

export default App;