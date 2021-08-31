# AgroBotics  

Projeto desenvolvido para introduzir conceitos de automação aplicados na agricultura durante a disciplina Tópicos Avançados em Engenharia de Biossistemas (ZEB1066) fornecida pela USP nas unidades EESC, ESALQ e FZEA.

<p align="center">
  <a href="#Projeto">Projeto</a> &nbsp; • &nbsp;
  <a href="#Organização">Organização</a> &nbsp; • &nbsp;
  <a href="#A fazer">A fazer</a> &nbsp; • &nbsp;
  <a href="#Tecnologias">Tecnologias</a>
</p>

### Projeto

O projeto foi desenvolvido a fim de simular o comportamento, em escala, de uma colheitadeira e um trator numa plantação. Assim, foi utilizado um seguidor de linha decorado para representar a colheitadeira e um outro robô para o trator, o qual segue a colheitadeira através da comunicação do protocolo ESP-NOW.
Para realizar o controle dos robôs foi utilizado o microcontrolador ESP-32, junto ao framework Arduino e outras bibliotecas complementares. O código foi desenvolvido na extensão PlatformIO do editor de texto Visual Studio Code.

### Organização

- <b>lib</b>: Bibliotecas desenvolvidas
    - <b>now:</b> Biblioteca para controlar a comunicação
    - <b>utils:</b> Biblioteca para controlar a movimentação
- <b>src:</b> Arquivos de implementação
    - <b>colheitadeira:</b> Algoritmo main.cpp da colheitadeira
    - <b>trator:</b> Algoritmo main.cpp do trator

### A fazer

- [x] Desenvolver biblioteca de comunicação
- [x] Desenvolver controle da movimentação 
- [ ] Desenvolver algoritmo de revezamento entre tratores
- [ ] Testar algoritmo

### Tecnologias

- <a href="https://www.arduino.cc/">Arduino</a>
- <a href="https://platformio.org/">PlatformIO</a>
- <a href="https://www.espressif.com/en/products/software/esp-now/overview">ESP-NOW (Espressif)</a>

---

Desenvolvido por Francisco Affonso e Rafael Saud
