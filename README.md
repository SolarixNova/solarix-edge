# Solarix: Sistema de Monitoramento de Energia Solar

### **Integrantes do Grupo**
- Mohamed Afif Smaili RM554445 
- Heitor Prestes RM 554823
- Lucca Ribeiro RM 556668

## **Descrição do Projeto**
O **Solarix** é um sistema desenvolvido com ESP32 no simulador Wokwi, projetado para monitorar parâmetros relacionados à energia solar, como eficiência, irradiação e luminosidade. O sistema calcula a energia solar gerada e exibe os dados em um display LCD, além de enviá-los via MQTT para o Node-RED, onde podem ser visualizados em um dashboard.

---

## **Principais Funcionalidades**
1. **Leitura de Sensores:**
   - **DHT22:** Mede temperatura e umidade.
   - **LDR:** Mede a luminosidade.
   - **Pinos Analógicos:** Recebem dados de irradiação e eficiência solar.

2. **Cálculo da Energia Solar Gerada:**
   - Com base nos valores de irradiação, eficiência e luminosidade, o sistema calcula a energia solar gerada (em Wh).

3. **Exibição no LCD:**
   - Exibe a energia gerada e a temperatura no display LCD I2C.

4. **Envio de Dados via MQTT:**
   - Publica os dados no tópico `fiap/solarix` para visualização e análise no Node-RED.

---

## **Componentes Utilizados**
- **ESP32:** Microcontrolador principal.
- **DHT22:** Sensor de temperatura e umidade.
- **LDR:** Sensor de luminosidade.
- **Display LCD I2C (16x2):** Exibição das informações coletadas.
- **Conexão Wi-Fi:** Para comunicação MQTT.
- **Broker MQTT:** `broker.hivemq.com`.

---

## **Como Funciona**
1. **Inicialização:**
   - O sistema conecta ao Wi-Fi e ao broker MQTT.
   - O LCD exibe mensagens iniciais.

2. **Loop Principal:**
   - Lê os valores dos sensores e realiza o cálculo da energia gerada.
   - Publica os dados no tópico MQTT.
   - Atualiza o display LCD com as informações.

3. **Dashboard Node-RED:**
   - Os dados enviados pelo ESP32 podem ser exibidos e monitorados em tempo real no Node-RED.

---

## **Como Executar no Wokwi**
1. **Simulador:**
   - Use o [Wokwi](https://wokwi.com/) para simular o código.
2. **Broker MQTT:**
   - Conecte-se ao broker `broker.hivemq.com`.
3. **Node-RED:**
   - Configure o Node-RED para receber os dados do tópico `fiap/solarix` e crie um dashboard para visualização.

---

## **Tópico MQTT**
- **Nome do Tópico:** `fiap/solarix`
- **Dados Publicados:**
  - Energia solar gerada (Wh).
  - Temperatura (°C).
  - Outros parâmetros (se necessário).

---

## **Pré-requisitos**
- Conta no Wokwi.
- Acesso ao Node-RED.
- Conhecimento básico em MQTT para configurar o broker e o dashboard.

---

## **Exemplo de Dados Publicados**
```json
{
  "energia": 150.45,
  "temperatura": 27.5,
  "umidade": 60,
  "luminosidade": 3200,
  "irradiacao": 800,
  "eficiencia": 85
}
