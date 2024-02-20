#include "Grammar.h"
#include "FiniteAutomaton.h"
#include <unordered_set>

FiniteAutomaton convertGrammarToAutomaton(Grammar grammar) 
{
	FiniteAutomaton automaton;
	automaton.setStates(grammar.getVn());
	automaton.setAlphabet(grammar.getVt());
	automaton.setInitialState(grammar.getStart());
	automaton.setFinalStates(grammar.getProduction(), grammar.getVn());
	automaton.initializationStates();
	automaton.initializationTransition(grammar.getProduction());
	return automaton;
}

void Menu(Grammar G) {

    if (G.isRegular() && G.verifyGrammar()) {
        FiniteAutomaton F = convertGrammarToAutomaton(G);
        while (true) {
            std::cout << std::endl;
            std::cout << "=== Meniu ===" << std::endl;
            std::cout << "1. Afiseaza gramatica" << std::endl;
            std::cout << "2. Genereaza cuvinte" << std::endl;
            std::cout << "3. Converteste gramatica in automat" << std::endl;
            std::cout << "4. Verifica cuvant" << std::endl;
            std::cout << "5. Genereaza si verifica cuvant" << std::endl;
            std::cout << "0. Iesire" << std::endl;
            std::cout << std::endl;
            short n,number;
            std::string s;
            std::unordered_set<std::string> set;
            std::cout << "Introduceti o comanda: ";
            std::cin >> n;

            switch(n)
            {
            case 1:
                G.printGrammar();
                break;

            case 2:
                short m;
                number = 0;
                std::cout << "Introduceti numarul de cuvinte pe care vreti sa le generati: ";
                std::cin >> m;
                set.clear();
                while (set.size() < m) {
                    set.insert(G.getGenerateWord());
                    if (number > 200) {
                        break;
                    }
                    number++;
                }
                if (number > 200){
                    std::cout << "Gramatica nu a putut genera atatea cuvinte!" << std::endl;
                    std::cout << "Toate cuvinte generate sunt: " ;
                    for (const auto& word : set) {
                        std::cout << word << " ";
                    }
                    std::cout << '\n';
                }
                else{

                    std::cout << "Cuvinte generate: ";
                    for (const auto& word : set) {
                        std::cout << word << " ";
                    }
                    std::cout << '\n';
                }
                std::cout << set.size();
                break;

            case 3:
               // F = convertGrammarToAutomaton(G);
                F.PrintAutomaton();
                break;

            case 4:
                s.clear();
                std::cout << "Introduceti un cuvant: ";
                std::cin >> s;
                if (F.CheckWord(G.getStart(), s)) {
                    std::cout << "Cuvantul este valid." << '\n';
                }
                else {
                    std::cout << "Cuvantul nu este valid." << '\n';
                }
                break;

            case 5:
                s.clear();
                s = G.getGenerateWord();
                std::cout << "Cuvantul generat este: " << s << '\n';
                if (F.CheckWord(F.getInitialState(), s)) {
                    std::cout << "Cuvantul este valid." << '\n';
                }
                else {
                    std::cout << "Cuvantul nu este valid." << '\n';
                }
                break;

            case 0:
                std::cout << "Hai Noroc:))" << std::endl;
                return;

            default:
                std::cout << "Comanda invalida. Incercati din nou." << std::endl;
            }
        }
    }
}

int main() {
    Grammar G;
    G.readGrammar();
    Menu(G);
    return 0;
}
