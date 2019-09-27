import React from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import Button from '@material-ui/core/Button';
import DoneIcon from '@material-ui/icons/Done';
import { Link } from "react-router-dom";
import Grid from '@material-ui/core/Grid';
import Fade from '@material-ui/core/Fade';
import { Redirect } from 'react-router';

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
    } else {
      this.setState({ showError: false });
    }
  };

  handleClick = param => e => {
    if (param === "unlock") {
      if (this.state.password === "1234") {
        console.log('this is correct!', param);
        this.handleError("noError");
        this.setState({ redirect: true });
      } else {
        this.handleError("error");
      }
    }
    else if (param === "delete") {
      this.setState({ password: '' });
      this.handleError("noError");
    } else {
      this.setState({ password: this.state.password + param });
      this.handleError("noError");
    }
  }

  render() {
    const { classes } = this.props;
    const { pinpadshown } = this.state;

    if (this.state.redirect) {
      return <Redirect push to="/unlocked" />;
    } else {
      return (
        <div className={classes.root}>
          <Grid container className="de">
            <Fade in={pinpadshown}>
              <Grid item xs={12}>
                <Link to="/" style={{ textDecoration: 'none', color: 'white' }}>
                  <Button variant="fab" color="primary" aria-label="Default" className={classes.button} style={{ marginTop: 400 , backgroundColor: '#0f9b34'}}>
                    <DoneIcon />
                  </Button>
                </Link>
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