Protótipo de braço robótico baseado no modelo Thor, desenvolvido para o componente curricular Projeto Integrador I.

Este projeto implementa o controle de um braço robótico utilizando um ESP32, responsável por ler sinais de sensores de fim de curso e acionar motores de passo NEMA 17 através de drivers DRV8825.
Tanto o esquemático quanto a placa de circuito impresso (PCB) foram desenvolvidos utilizando o KiCAD.

A operação do robô é realizada por meio de uma interface web, que se comunica com o sistema através de WebSocket. As angulações de cada junta são enviadas para um servidor em Python, onde são processadas e convertidas em instruções de movimento. Em seguida, o servidor envia ao ESP32 os valores de rotação necessários para cada junta.
