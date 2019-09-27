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

const styles = theme => ({
  root: {
    display: 'flex',
    flexWrap: 'wrap',
  },
  margin: {
    margin: theme.spacing.unit,
  },
  withoutLabel: {
    marginTop: theme.spacing.unit * 3,
  },
  textField: {
    flexBasis: 200,
  },
  button: {
    margin: theme.spacing.unit+10,
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
  };

  handleChange = prop => event => {
    this.setState({ [prop]: event.target.value });
  };

  handleClickShowPassword = () => {
    this.setState(state => ({ showPassword: !state.showPassword }));
  };

  handleClick() {
    console.log('this is:', this);
  }

  render() {
    const { classes } = this.props;

    return (
      <div className={classes.root}>
        <Grid container className="de">
          <Grid item xs={12}>
            <Grid key="password" item>
            <span key="pass">
              <FormControl className={classNames(classes.margin, classes.textField)}>
                <InputLabel htmlFor="adornment-password">Please enter your code</InputLabel>
                <Input
                  id="adornment-password"
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
                <FormHelperText id="weight-helper-text">1234</FormHelperText>
              </FormControl>
              <br/>
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
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("1")}>1</Button>
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("2")}>2</Button>
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("3")}>3</Button>
                </Grid>
              <br />
              <Grid key="456" item>
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("4")}>4</Button>
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("5")}>5</Button>
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("6")}>6</Button>
                </Grid>
              <br />
              <Grid key="789" item>
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("7")}>7</Button>
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("8")}>8</Button>
                  <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("9")}>9</Button>
                </Grid>
              <br />
              <Grid key="0okback" item>
                <Button variant="fab" color="primary" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("delete")}>
                  <BackIcon />
                </Button>
                <Button variant="fab" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("0")}>
                  0
                </Button>
                <Button variant="fab" color="primary" aria-label="Add" className={classes.button} onClick={this.handleClick.bind("unlock")}>
                  <UnlockIcon />
                </Button>
              </Grid>
              </span>
            </Grid>
          </Grid>
        </Grid>
      </div>
    );
  }
}

NumPad.propTypes = {
  classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(NumPad);
