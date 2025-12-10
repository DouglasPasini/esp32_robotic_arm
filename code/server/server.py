from flask import Flask, render_template
import asyncio
import websockets
import threading
import json

app = Flask(__name__)


# --- Flask / Interface Web ---

@app.route('/')
def index():
    return render_template('index.html')

def start_flask():
    app.run(host="0.0.0.0", port=5000, debug=True, use_reloader=False)


# --- Gerenciamento de Clientes ---

web_clients = set()
esp_clients = set()

def register_client(websocket, who):
    if who == "web":
        web_clients.add(websocket)
        print("[WS] Cliente WEB conectado")
    elif who == "esp":
        esp_clients.add(websocket)
        print("[WS] Cliente ESP conectado")


def unregister_client(websocket):
    if websocket in web_clients:
        web_clients.remove(websocket)
        print("[WS] Cliente WEB desconectado")
    if websocket in esp_clients:
        esp_clients.remove(websocket)
        print("[WS] Cliente ESP desconectado")


#  --- Roteamento de Mensagens ---

async def route_message(websocket, data):
    msg_type = data.get("type")

    if msg_type in message_handlers:
        await message_handlers[msg_type](websocket, data)
    else:
        print(f"[WARN] Tipo de mensagem desconhecido: {msg_type}")



# --- Handlers por Tipo de Mensagem ---

async def handle_client_identification(websocket, data):
    # Handler que identifica quem se conectou
    who = data.get("who")
    register_client(websocket, who)


async def handle_generic_joint(websocket, data):
    # Handler que apenas repassa o valor do ângulo para o esp
    angle = data.get("angle")
    #print(f"[CMD] {data['type']} -> {angle}°")
    
    if websocket in web_clients:
        for esp in esp_clients:
            await esp.send(json.dumps(data))

async def handle_sensor_state(websocket,data):
    # Handler que apenas repassa o valor do sensor para a web
    # Apenas o ESP deve enviar essas mensagens
    if websocket in esp_clients:
        for web in web_clients:
            await web.send(json.dumps(data))

# mapa de handlers
message_handlers = {
    "client": handle_client_identification,
    "gripper": handle_generic_joint,
    "joint56": handle_generic_joint,
    "joint4": handle_generic_joint,
    "joint3": handle_generic_joint,
    "joint2": handle_generic_joint,
    "base": handle_generic_joint,
    "sensor": handle_sensor_state
}


# --- Hanlder Princpal do Websocket ---

async def handler(websocket):
    print("[WS] Cliente conectou")

    try:
        async for message in websocket:
            try:
                data = json.loads(message)
                await route_message(websocket, data)

            except json.JSONDecodeError:
                print("[ERRO] Mensagem não é JSON:", message)

    except websockets.ConnectionClosed:
        print("[WS] Conexão fechada")

    finally:
        unregister_client(websocket)

# --- Servidor Websocket ---

async def main():
    async with websockets.serve(handler, "0.0.0.0", 8000):
        print("[WS] Servidor WebSocket rodando na porta 8000")
        await asyncio.Future()  # Mantém rodando


# --- Execução ---

if __name__ == "__main__":
    flask_thread = threading.Thread(target=start_flask, daemon=True)
    flask_thread.start()

    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nServidor encerrado")
