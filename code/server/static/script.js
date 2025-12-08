const controlsConfig = [
    {
        id: "gripper",
        label: "Garra",
        type: "gripper",
        move: null,
        min: 0,
        max: 180,
        initial: 0,
        controlType: "slider",
        sensorId: "gripper"
    },
    {
        id: "joint_56_rot",
        label: "Rotação Junta 56",
        type: "joint56",
        move: "rotate",
        controlType: "buttons",
        sensorId: "joint_56_rot"
    },
    {
        id: "joint_56_tilt",
        label: "Inclinação Junta 56",
        type: "joint56",
        move: "tilt",
        controlType: "buttons",
        sensorId: "joint_56_tilt"
    },
    {
        id: "joint_4_rot",
        label: "Rotação Junta 4",
        type: "joint4",
        move: "rotate",
        controlType: "buttons",
        sensorId: "joint_4_rot"
    },
    {
        id: "joint_3_tilt",
        label: "Inclinação da Junta 3",
        type: "joint3",
        move: "tilt",
        controlType: "buttons",
        sensorId: "joint_3_tilt"
    },
    {
        id: "joint_2_tilt",
        label: "Inclinação da Junta 2",
        type: "joint2",
        move: "tilt",
        controlType: "buttons",
        sensorId: "joint_2_tilt"
    },
    {
        id: "base_rot",
        label: "Rotação da Base",
        type: "base",
        move: "rotate",
        controlType: "buttons",
        sensorId: "base_rot"
    }
];


// === WEBSOCKET ===
const socket = new WebSocket("ws://192.168.0.200:8000");

socket.addEventListener("open", () => {
    console.log("WS conectado!");
    socket.send(JSON.stringify({ type: "client", who: "web" }));
});

socket.addEventListener("message", (event) => {
    const msg = JSON.parse(event.data);

    if (msg.sensor) {
        const indicator = sensorIndicators[msg.sensor];
        if (indicator) {
            if (msg.state === 1) indicator.classList.add("sensor-active");
            else indicator.classList.remove("sensor-active");
        }
    }
});

function sendCommand(cmd) {
    if (socket.readyState === WebSocket.OPEN) {
        socket.send(JSON.stringify(cmd));
    }
}

// === BOTÕES COM HOLD ===
function setupHoldButton(element, callback) {
    let interval = null;

    const start = () => {
        callback();
        interval = setInterval(callback, 500);
    };

    const stop = () => {
        clearInterval(interval);
        interval = null;
    };

    element.addEventListener("mousedown", start);
    element.addEventListener("touchstart", start);

    element.addEventListener("mouseup", stop);
    element.addEventListener("mouseleave", stop);
    element.addEventListener("touchend", stop);
}

// Armazena os quadradinhos para acesso rápido
const sensorIndicators = {};



// === CRIAÇÃO DA INTERFACE ===
function createControls() {
    const container = document.getElementById("controls");

    controlsConfig.forEach(ctrl => {
        const wrapper = document.createElement("div");
        wrapper.className = "control-box";

        const label = document.createElement("label");
        label.textContent = ctrl.label;

        // === CASO 1: SLIDER (GRIPPER) ===
        if (ctrl.controlType === "slider") {
            const slider = document.createElement("input");
            slider.type = "range";
            slider.min = ctrl.min;
            slider.max = ctrl.max;
            slider.value = ctrl.initial;
            slider.className = "slider";

            const valueDisplay = document.createElement("div");
            valueDisplay.className = "control-value";
            valueDisplay.textContent = ctrl.initial;

            slider.addEventListener("input", () => {
                const value = parseInt(slider.value);
                valueDisplay.textContent = value;

                sendCommand({
                    type: ctrl.type,
                    angle: value
                });
            });
            // Indicador de fim de curso
            const indicator = document.createElement("div");
            indicator.className = "sensor-indicator";

            // Guarda no dicionário para atualizar depois via WebSocket
            sensorIndicators[ctrl.sensorId] = indicator;


            wrapper.appendChild(label);            
            wrapper.appendChild(slider);
            wrapper.appendChild(valueDisplay);
            container.appendChild(wrapper);
            return;
        }

        // === CASO 2: BOTÕES (OUTRAS JUNTAS) ===

        const minusBtn = document.createElement("button");
        minusBtn.className = "control-btn";
        minusBtn.textContent = "−";

        const plusBtn = document.createElement("button");
        plusBtn.className = "control-btn";
        plusBtn.textContent = "+";

        function sendStep(delta) {
            const command = {
                type: ctrl.type,
                move: ctrl.move,
                step: delta   // <-- Aqui vai +1 ou -1
            };

            sendCommand(command);
        }

        // Movimento contínuo
        setupHoldButton(plusBtn, () => sendStep(+1));
        setupHoldButton(minusBtn, () => sendStep(-1));

        // Indicador de fim de curso
        const indicator = document.createElement("div");
        indicator.className = "sensor-indicator";

        // Guarda no dicionário para atualizar depois via WebSocket
        sensorIndicators[ctrl.sensorId] = indicator;


        wrapper.appendChild(minusBtn);
        wrapper.appendChild(label);
        wrapper.appendChild(plusBtn);
        wrapper.appendChild(indicator);

        container.appendChild(wrapper);

    });
}

createControls();
