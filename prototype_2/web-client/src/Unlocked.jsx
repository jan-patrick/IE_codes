import React from 'react';
import Unlock from './Success.js';
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
        <Unlock></Unlock>
      </div>
    )
  }
}

export default Login;