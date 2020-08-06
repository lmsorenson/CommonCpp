import React from 'react';
import logo from './logo.svg';
import './App.css';

class App extends React.Component {
  
  constructor(props: any)
  {
    super(props);

    document.title = 'PL | Documentation'
  }

  public render()
  {
    return (
        <div className="App">
          <title>Page</title>
          <header className="App-header">
            <img src={logo} className="App-logo" alt="logo" />
            <p>
              CommonCpp page
            </p>
          </header>
        </div>
    );
  }
}

export default App;
