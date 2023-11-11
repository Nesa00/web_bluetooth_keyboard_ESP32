const char PAGE_MAIN[] PROGMEM = R"=====(


<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Custom Keyboard</title>

    <!-- Link to Roboto font from Google Fonts -->
    <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&display=swap">

    <style>
        body {
            display: flex;
            align-items: center;
            justify-content: center;
            height: 100vh;
            margin: 0;
            font-size: 25px;
            font-family: 'Roboto', sans-serif; /* Use Roboto font for the body */
            background: #c33764;
            background: -webkit-linear-gradient(to bottom, #1d713d, rgb(55, 139, 195));
            background: linear-gradient(to bottom, #1d713d, rgb(55, 139, 195));
        }

        .keyboard {
            display: flex;
            flex-direction: column; /* Stack rows vertically */
            align-items: center; /* Center items horizontally */
        }

        .row {
            display: flex;
        }

        .key {
            width: 60px;
            height: 60px;
            text-align: center;
            line-height: 60px; /* Set line-height equal to height to center text vertically */
            cursor: pointer;
            transition: background-color 0.3s ease;
            margin: 5px; /* Adjust margin for spacing */
            border-radius: 8px; /* Add border radius to create rounded corners */
            user-select: none; /* This makes the element unselectable */
            background: rgb(255, 255, 255);
            background: -webkit-linear-gradient(to bottom, #ffffff, rgb(146, 147, 148));
            background: linear-gradient(to bottom, #ffffff, rgb(146, 147, 148));
        }

        .key:hover {
            background: -webkit-linear-gradient(to top, rgb(28, 145, 223), #1164c2);
            background: linear-gradient(to top, rgb(28, 145, 223), #1164c2);
        }
    </style>
</head>

<body>
    <div id="keyboard" class="keyboard"></div>
        <script>
            const keyboardLayout = [
                ['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'],
                ['', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ''],
                ['↑', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '<<'],
                ['12!@', 'space', 'enter'],
            ];
        
            const keyboardElement = document.getElementById('keyboard');
        
            // Variable to track if shift is pressed
            let shiftPressed = false;
        
            function createKeyboard() {
                for (let i = 0; i < keyboardLayout.length; i++) {
                    const row = keyboardLayout[i];
                    const rowElement = document.createElement('div');
                    rowElement.className = 'row';
        
                    for (let j = 0; j < row.length; j++) {
                        const symbol = row[j];
        
                        // Skip creating elements for empty strings
                        if (symbol !== '') {
                            const keyElement = document.createElement('div');
                            keyElement.className = 'key';
                            keyElement.textContent = symbol;
        
                            if (symbol === 'space' || symbol === 'SPACE') {
                                keyElement.style.width = '460px';
                            }
        
                            if (symbol === 'enter' || symbol === 'ENTER' || symbol === '12!@') {
                                keyElement.style.width = '100px';
                            }
        
                            if (symbol === '') {
                                keyElement.style.width = '20px';
                            }
        
                            if (symbol === '↑' || symbol === '↓' ||symbol === '<<') {
                                keyElement.style.width = '90px';
                            }
        
                            // Attach click event listener to each key
                            keyElement.addEventListener('click', () => sendSymbol(symbol));
        
                            rowElement.appendChild(keyElement);
                        }
                    }
        
                    keyboardElement.appendChild(rowElement);
                }
            }
        
            function toggleCase() {
                // Toggle the shift state
                shiftPressed = !shiftPressed;

                // Loop through all keys and toggle their case
                const keys = document.querySelectorAll('.key');
                keys.forEach(key => {
                    const currentText = key.textContent;
                    key.textContent = shiftPressed ? currentText.toUpperCase() : currentText.toLowerCase();

                    // Check if the current key is the Caps Lock button
                    if (currentText === '↑' || currentText === '↓') {
                        // Change the Caps Lock symbol based on the state
                        key.textContent = shiftPressed ? '↓' : '↑';
                    }
                });
            }

        
            function sendSymbol(symbol) {
                // Handle special actions for certain keys
                if (symbol === '↑' || symbol === '↓') {
                    toggleCase();
                } else {
                    // console.log(shiftPressed)
                    if (shiftPressed) {
                        symbol = symbol.toUpperCase();
                    } else {
                        symbol = symbol.toLowerCase();
                    }
                    // Send the symbol to the server (Arduino) for processing
                    var xhr = new XMLHttpRequest();
                    xhr.open("GET", "/symbol?symbol=" + encodeURIComponent(symbol), true);
                    xhr.send();
                }
        
                console.log('Symbol pressed:', symbol);
            }
        
            createKeyboard();
        </script>

</body>

</html>

)=====";