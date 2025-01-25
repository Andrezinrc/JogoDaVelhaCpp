#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <memory>

using namespace std;

class JogoDaVelha {
private:
    char tabuleiro[3][3];
    char jogadorAtual;
    bool modoBot;
    
public:
    JogoDaVelha(bool jogarContraBot) : modoBot(jogarContraBot) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                tabuleiro[i][j] = ' ';
            }
        }
        // o jogador inicia com X
        jogadorAtual = 'X';
    }

    void mostrarTabuleiro() {
       //limpa o terminal
        system("clear");// para win system("cls");

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tabuleiro[i][j] == 'X') {
                    cout << "\033[31m" << " " << tabuleiro[i][j] << " " << "\033[0m";
                } else if (tabuleiro[i][j] == 'O') {
                    cout << "\033[33m" << " " << tabuleiro[i][j] << " " << "\033[0m";
                } else {
                    cout << " " << tabuleiro[i][j] << " ";
                }
                if (j < 2) cout << "\033[34m|\033[0m";
            }
            cout << endl;

            if (i < 2) cout << "\033[34m---|---|---\033[0m" << endl;
        }
    }

    bool verificarVitoria() {
        for (int i = 0; i < 3; i++) {
            //verifica linhas
            if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') return true;
            // verifica colunas
            if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ') return true;
        }

        //verifica as diagonais
        if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') return true;
        if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ') return true;

        return false;
    }

    //verifica empate
    bool verificarEmpate() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tabuleiro[i][j] == ' ') return false;
            }
        }
        return true;
    }

    void botJogar() {
        //bot tenta vencer ou bloquear
        for (char jogador : {'O', 'X'}) {
            for (int i = 0; i < 3; i++) {
                //verifica linhas e colunas
                if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == ' ') { tabuleiro[i][2] = 'O'; return; }
                if (tabuleiro[i][0] == jogador && tabuleiro[i][2] == jogador && tabuleiro[i][1] == ' ') { tabuleiro[i][1] = 'O'; return; }
                if (tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador && tabuleiro[i][0] == ' ') { tabuleiro[i][0] = 'O'; return; }

                if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == ' ') { tabuleiro[2][i] = 'O'; return; }
                if (tabuleiro[0][i] == jogador && tabuleiro[2][i] == jogador && tabuleiro[1][i] == ' ') { tabuleiro[1][i] = 'O'; return; }
                if (tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador && tabuleiro[0][i] == ' ') { tabuleiro[0][i] = 'O'; return; }
            }

            //verifica  diagonais
            if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == ' ') { tabuleiro[2][2] = 'O'; return; }
            if (tabuleiro[0][0] == jogador && tabuleiro[2][2] == jogador && tabuleiro[1][1] == ' ') { tabuleiro[1][1] = 'O'; return; }
            if (tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador && tabuleiro[0][0] == ' ') { tabuleiro[0][0] = 'O'; return; }

            if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == ' ') { tabuleiro[2][0] = 'O'; return; }
            if (tabuleiro[0][2] == jogador && tabuleiro[2][0] == jogador && tabuleiro[1][1] == ' ') { tabuleiro[1][1] = 'O'; return; }
            if (tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador && tabuleiro[0][2] == ' ') { tabuleiro[0][2] = 'O'; return; }
        }

        //o bot ira jogar no centro se estiver livre
        if (tabuleiro[1][1] == ' ') { tabuleiro[1][1] = 'O'; return; }

        // joga em um canto disponivel
        int cantos[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
        for (auto& canto : cantos) {
            if (tabuleiro[canto[0]][canto[1]] == ' ') {
                tabuleiro[canto[0]][canto[1]] = 'O';
                return;
            }
        }

        //joga na primeira posicao disponivel
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tabuleiro[i][j] == ' ') {
                    tabuleiro[i][j] = 'O';
                    return;
                }
            }
        }
    }

    void jogar() {
        int linha, coluna;
        bool vitoria = false;

        while (!vitoria && !verificarEmpate()) {
            mostrarTabuleiro();

            if (jogadorAtual == 'X') {

                cout << "\033[36mJogador " << jogadorAtual << ", faça sua jogada (linha e coluna [1-3]): \033[0m";
                cin >> linha >> coluna;

                linha -= 1;
                coluna -= 1;

                if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && tabuleiro[linha][coluna] == ' ') {
                    tabuleiro[linha][coluna] = jogadorAtual;
                } else {
                    cout << "\033[31mJogada inválida! Tente novamente.\033[0m" << endl;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    continue;
                }
            } else {

                if (modoBot) {
                    botJogar();
                } else {
                    cout << "\033[33mJogador " << jogadorAtual << ", faça sua jogada (linha e coluna [1-3]): \033[0m";
                    cin >> linha >> coluna;

                    linha -= 1;
                    coluna -= 1;

                    if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && tabuleiro[linha][coluna] == ' ') {
                        tabuleiro[linha][coluna] = jogadorAtual;
                    } else {
                        cout << "\033[31mJogada inválida! Tente novamente.\033[0m" << endl;
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        continue;
                    }
                }
            }

            vitoria = verificarVitoria();
            jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
        }

        mostrarTabuleiro();

        if (vitoria) {
            cout << "\033[32mJogador " << (jogadorAtual == 'X' ? 'O' : 'X') << " venceu!\033[0m" << endl;
        } else {
            cout << "\033[37mEmpate!\033[0m" << endl;
        }
    }

    ~JogoDaVelha() {
        cout << "\033[31mO Jogo terminou.\033[0m" << endl;
    }
};

int main() {
    int escolha;
    
    cout << "\033[36mEscolha o modo de jogo:\033[0m" << endl;
    cout << "\033[36m1 - Jogar contra um amigo\033[0m" << endl;
    cout << "\033[36m2 - Jogar contra o bot\033[0m" << endl;
    cout << "\033[36mEscolha: \033[0m";
    cin >> escolha;

    bool jogarContraBot = (escolha == 2);

    auto jogo = make_shared<JogoDaVelha>(jogarContraBot);
    jogo->jogar();

    // JogoDaVelha* jogo = new JogoDaVelha();
    // jogo->jogar();

    // delete jogo;
    // jogo = nullptr
    
    return 0;
}
