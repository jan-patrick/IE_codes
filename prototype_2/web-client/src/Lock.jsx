import React from 'react';
import Lock from './Numpad.js';
import Navbar from './Navbar.js';

class Login extends React.Component {

  constructor() {
    super();
    this.state = {
      redirectToReferrer: false
    }
  }

  render() {

    return (
      <div>
        <Navbar></Navbar>
        <Lock></Lock>
      </div>
    )
  }
}

export default Login;