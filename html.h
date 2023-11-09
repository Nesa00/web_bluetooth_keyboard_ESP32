const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web Keyboard</title>
    <style>
        .keyboard {
            display: flex;
            flex-wrap: wrap;
            max-width: 550px;
            margin: 0 auto;
        }

        .key {
            width: 40px;
            height: 40px;
            text-align: center;
            line-height: 40px;
            border: 1px solid #000;
            margin: 5px;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }

        .key:hover {
            background-color: #38E7A4; /* Change the background color on hover */
        }
    </style>
</head>

<body>
    <div id="keyboard" class="keyboard"></div>

    <script>
        const keyboardLayout = [
            '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
            'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
            'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?'
            //'!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
            //'_', '+', '-', '=', '{', '}', '[', ']', '|', '\\',
            //':', ';', '"', '\'', '<', '>', ',', '.', '?'
            // Add more symbols as needed
        ];

        const keyboardElement = document.getElementById('keyboard');

        function createKeyboard() {
            keyboardLayout.forEach(symbol => {
                const keyElement = document.createElement('div');
                keyElement.className = 'key';
                keyElement.textContent = symbol;
                keyElement.addEventListener('click', () => sendSymbol(symbol));
                keyboardElement.appendChild(keyElement);
            });
        }

        function sendSymbol(symbol) {
            // Send the symbol to the server (Arduino) for processing
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/symbol?symbol=" + symbol, true);
            xhr.send();
            
            // Log the symbol to the console
            console.log('Symbol pressed:', symbol);
        }

        createKeyboard();
    </script>
</body>

</html>


)=====";