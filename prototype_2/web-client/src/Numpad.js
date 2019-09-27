import React from 'react';
import classNames from 'classnames';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import IconButton from '@material-ui/core/IconButton';
import Input from '@material-ui/core/Input';
import InputLabel from '@material-ui/core/InputLabel';
import InputAdornment from '@material-ui/core/InputAdornment';
import FormHelperText from '@material-ui/core/FormHelperText';
import FormControl from '@material-ui/core/FormControl';
import Visibility from '@material-ui/icons/Visibility';
import VisibilityOff from '@material-ui/icons/VisibilityOff';
import Button from '@material-ui/core/Button';
import BackIcon from '@material-ui/icons/KeyboardArrowLeft';
import UnlockIcon from '@material-ui/icons/LockOpen';
import Grid from '@material-ui/core/Grid';
import Fade from '@material-ui/core/Fade';
import { Redirect } from 'react-router';
import Websocket from 'react-websocket';

const styles = theme => ({
  root: {
    display: 'flex',
    flexWrap: 'wrap',
  },
  margin: {
    margin: theme.spacing.unit + 10,
  },
  withoutLabel: {
    marginTop: theme.spacing.unit * 3,
  },
  textField: {
    flexBasis: 200,
  },
  button: {
    margin: theme.spacing.unit + 10,
    height: 80,
    width: 80,
    fontSize: 25,
  },
  input: {
    fontSize: 25,
  },
  extendedIcon: {
    marginRight: theme.spacing.unit,
  },
});

class NumPad extends React.Component {
  state = {
    showPassword: false,
    showError: false,
    password: '',
    pinpadshown: true,
    redirect: false,
  };

  handleChange = prop => event => {
    this.setState({ [prop]: event.target.value });
  };

  handleClickShowPassword = () => {
    this.setState(state => ({ showPassword: !state.showPassword }));
  };

  handleError = param => {
    if (param === "error") {
      this.setState({ showError: true });
      // ledRed 2 ON, 3 OFF
      this.sendMessage(2);
    } else {
      this.setState({ showError: false });
      this.sendMessage(3);
    }
  };

  handleClick = param => e => {
    if (param === "unlock" || param === "#") {
      if (this.state.password === "1234") {
        console.log('this is correct!', param);
        this.handleError("noError");
        this.sendMessage(0);
        this.setState({ redirect: true });
        // ledGreen 0 ON, 1 OFF
        
      } else {
        this.handleError("error");
        this.sendMessage(1);
      }
    }
    else if (param === "delete") {
      this.setState({ password: this.state.password.substring(0, this.state.password.length - 1) });
      this.handleError("noError");
      this.sendMessage(5)
    } else {
      this.setState({ password: this.state.password + param });
      this.handleError("noError");
      this.sendMessage(5)
    }
  }

  handleData(data) {
    console.log(String(data));
    this.handleClick(data)();
  }

  handleOpen()  {
    console.log("connected:)");
  }
  handleClose() {
    console.log("disconnected:(");
  }

  sendMessage(message){
    if(message !== null){
      this.refWebSocket.sendMessage(message);
    }
  }

  render() {
    const { classes } = this.props;
    const { pinpadshown } = this.state;

    if (this.state.redirect) {
      // 4 all LEDs ON, 5 all LEDs OFF
      return (
        <Redirect push to="/unlocked" />
      );
    } else {
      return (
        <div className={classes.root}>
        <Websocket url='ws://localhost:8080/' onMessage={this.handleData.bind(this)} onOpen={this.handleOpen} onClose={this.handleClose} reconnect={true} debug={true} ref={Websocket => {this.refWebSocket = Websocket;}}/>
          <Grid container className="de">
            <Fade in={pinpadshown}>
              <Grid item xs={12}>
                <Grid key="password" item>
                  <span key="pass">
                    <FormControl className={classNames(classes.margin, classes.textField)}>
                      <InputLabel htmlFor="adornment-password">Please enter your code</InputLabel>
                      <Input
                        id="adornment-password"
                        error={this.state.showError}
                        type={this.state.showPassword ? 'text' : 'password'}
                        value={this.state.password}
                        onChange={this.handleChange('password')}
                        endAdornment={
                          <InputAdornment position="end">
                            <IconButton
                              aria-label="Toggle password visibility"
                              onClick={this.handleClickShowPassword}
                            >
                              {this.state.showPassword ? <Visibility /> : <VisibilityOff />}
                            </IconButton>
                          </InputAdornment>
                        }
                      />
                      <FormHelperText id="weight-helper-text"></FormHelperText>
                    </FormControl>
                    <br />
                  </span>
                </Grid>
                <Grid
                  container
                  spacing={16}
                  className="test"
                  direction="row"
                  justify="space-evenly"
                  alignItems="flex-start"
                >
                  <span key="1-3">
                    <Grid key="123" item>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(1)}>1</Button>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(2)}>2</Button>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(3)}>3</Button>
                    </Grid>
                    <br />
                    <Grid key="456" item>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(4)}>4</Button>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(5)}>5</Button>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(6)}>6</Button>
                    </Grid>
                    <br />
                    <Grid key="789" item>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(7)}>7</Button>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(8)}>8</Button>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(9)}>9</Button>
                    </Grid>
                    <br />
                    <Grid key="0okback" item>
                      <Button variant="fab" color="primary" aria-label="Add" className={classes.button} onClick={this.handleClick("delete")}>
                        <BackIcon />
                      </Button>
                      <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick(0)}>
                        0
                      </Button>
                      <Button variant="fab" color="primary" aria-label="Default" className={classes.button} onClick={this.handleClick("unlock")}>
                        <UnlockIcon />
                      </Button>
                    </Grid>
                  </span>
                </Grid>
              </Grid>
            </Fade>
          </Grid>
        </div>
      );
    }
  }
}

NumPad.propTypes = {
  classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(NumPad);