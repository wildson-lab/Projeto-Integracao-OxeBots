#Descrição
Este projeto consiste em um sistema de iluminação inteligente, que realiza o monitoramento de tensão, corrente e temperatura em dois postes, e envia estes parâmetros para uma central de controle.

# Instruções de uso
* Baixe todo este diretório para o seu computador;
* Instale as bibliotecas "Arduino" e "RF" no seu Proteus, (bibliotecas disponíveis em Circuito/Bibliotecas);
* Abra o arquivo PROJECT_ARDUINO_2.0-1.pdsprj, na pasta Circuito;
* Dê dois cliques em cada Arduino Uno (escravo). Em "Program file", selecione o arquivo ".pio/build/controlador/firmware.hex". A seguir, clique em "OK";
* Dê dois cliques no Arduino Mega (mestre). Em "Program file", selecione o arquivo ".pio/build/concentrador/firmware.hex". A seguir, clique em "OK";
* Execute a simulação, experimentando alterar os valores de tensão, temperatura e corrente em cada poste, bem como a posição da célula fotoelétrica;
* Para alternar entre os postes no Arduino mestre, pressione o botão conectado a "INT_M". O número do poste será mostrado abaixo da letra "P" no display mestre;
