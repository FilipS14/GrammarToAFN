#include"FiniteAutomaton.h"
#include <queue>
FiniteAutomaton::FiniteAutomaton(std::vector<char> states,
	std::vector<char>alphabet,
	char initaialState, 
	std::vector<char> finalStates) :
	
	m_states{ states },
	m_alphabet{ alphabet },
	m_initialState{ initaialState },
	m_finalStates{finalStates }
	{}

FiniteAutomaton::FiniteAutomaton(const FiniteAutomaton& other) {
	m_states = other.m_states;
	m_alphabet = other.m_alphabet;
	m_initialState = other.m_initialState;
	m_transition = other.m_transition;
	m_finalStates = other.m_finalStates;
}

bool FiniteAutomaton::VerifyInitailStateToFinalState()
{
	std::queue<char> stateQueue;
	std::unordered_set<char> visitedStates;

	stateQueue.push(m_initialState);

	while (!stateQueue.empty()) {
		
		char currentState = stateQueue.front();
		stateQueue.pop();

		if (std::find(m_finalStates.begin(), m_finalStates.end(), currentState) != m_finalStates.end()) {
			return true;
		}

		visitedStates.insert(currentState);

		if (m_transition.find(currentState) != m_transition.end()) {
			for (const auto& transition : m_transition[currentState]) {

				const std::vector<char>& nextStates = transition.second;
				
				for (char nextState : nextStates) {
					if (visitedStates.find(nextState) == visitedStates.end()) {
						stateQueue.push(nextState);
					}
				}
			}
		}
	}

	return false;
}

bool FiniteAutomaton::VerifyUniqueStates()
{
	std::unordered_set UniqueStates(m_states.begin(), m_states.end());
	return UniqueStates.size() == m_states.size();
}

bool FiniteAutomaton::VerifyUniqueAlphabet()
{
	std::unordered_set UniqueAlphabet(m_alphabet.begin(), m_alphabet.end());
	return UniqueAlphabet.size() == m_alphabet.size();
}

bool FiniteAutomaton::VerifyIntialState()
{
	return std::find(m_states.begin(), m_states.end(), m_initialState) != m_states.end();
}

bool FiniteAutomaton::VerifyFinalState()
{
	for (const auto& word : m_finalStates)
	{
		if (std::find(m_states.begin(), m_states.end(), word) == m_states.end())
			return false;
	}
	return true;
}

bool FiniteAutomaton::VerifyTransitions()
{
	for (const auto& transition : m_transition) {
		char currentState = transition.first;

		if (!IsValidState(currentState)) {
			return false;
		}

		for (const auto& nextStateTransition : transition.second) {
			char nextState = nextStateTransition.first;

			if (!IsValidSymbol(nextState)) {
				return false;
			}

			for (const auto& symbol : nextStateTransition.second) {
				if (!IsValidState(symbol)) {
					return false;
				}
			}
		}
	}
	return true;
}

bool FiniteAutomaton::IsValidState(char state) const {
	return std::find(m_states.begin(), m_states.end(), state) != m_states.end();
}

bool FiniteAutomaton::IsValidSymbol(char symbol) const {
	return std::find(m_alphabet.begin(), m_alphabet.end(), symbol) != m_alphabet.end();
}

bool FiniteAutomaton::VerifyAutomaton() {
	
	return VerifyUniqueStates() &&
		VerifyUniqueAlphabet() &&
		VerifyIntialState() &&
		VerifyFinalState() &&
		VerifyTransitions() &&
		VerifyInitailStateToFinalState();
}

bool FiniteAutomaton::CheckWord(const char& currentState, const std::string& currentWord) const
{
	if (currentWord.empty() || currentWord[0] == '@')
	{
		return std::find(m_finalStates.begin(), m_finalStates.end(), currentState) != m_finalStates.end();
	}

	auto it = m_transition.find(currentState);
	if (it != m_transition.end()) {
		char nextTransitionState = currentWord[0];
		auto transitionIt = it->second.find(nextTransitionState);

		if (transitionIt != it->second.end()) {
			for (const auto& nextState : transitionIt->second) {
				bool found = CheckWord(nextState, currentWord.substr(1));
				if (found) return true;
			}
		}
	}

	return false;
}


//--------------------------------------------
bool FiniteAutomaton::IsDeterministic() 
{
	for (const auto& stateFunction : m_transition)
	{
		std::unordered_map<char, std::vector<char>> possibleScenarios = stateFunction.second;
		for (const auto& nextState : possibleScenarios)
		{
			if (nextState.second.size() > 1) return false;
		}
	}
	return true;
}

void FiniteAutomaton::PrintAutomaton() {
	for (const auto& transition : m_transition) {
		char key = transition.first;

		for (const auto& entry : transition.second) {
			char value1 = entry.first;

			std::cout << key << "-" << value1 << "->";

			const std::vector<char>& vectorValue = entry.second;

			for (const auto& element : vectorValue) {
				std::cout << element << " ";
			}

			std::cout << '\n';
		}
	}
}

//futhermore
void FiniteAutomaton::initializationStates(){
	m_states.emplace_back(m_finalStates.at(0));
}

void FiniteAutomaton::initializationTransition(std::vector<std::pair<std::string, std::string>> production) {
	for (const auto& word : production) {
		char key = word.first[0];
		char value1 = word.second[0];

		if (value1 == '@')
			continue;

		std::vector<char> vectorValue(word.second.begin() + 1, word.second.end());

		if (vectorValue.empty()) {
			vectorValue.emplace_back(m_finalStates.at(0));
		}

		if (m_transition.find(key) == m_transition.end()) {
			
			std::unordered_map<char, std::vector<char>> map;
			map[value1] = vectorValue;
			m_transition[key] = map;
		}
		else {
			auto& map = m_transition[key];
			if (map.find(value1) == map.end()) {
				map[value1] = vectorValue;
			}
			else {
				map[value1].insert(map[value1].end(), vectorValue.begin(), vectorValue.end());
			}
		}
	}
}

//define setters
void FiniteAutomaton::setStates(std::vector<char> states) {
	m_states = states;
}

void FiniteAutomaton::setAlphabet(std::vector<char>alphabet) {
	m_alphabet = alphabet;
}

void FiniteAutomaton::setInitialState(char initialState) {
	m_initialState = initialState;
}

void FiniteAutomaton::setTransition(std::unordered_map<char, std::unordered_map<char, std::vector<char>>> transition) {
	m_transition = transition;
}

void FiniteAutomaton::setFinalStates(std::vector<std::pair<std::string, std::string>> production,std::vector<char>state ) {
	char ch = state.at(0);
	while (std::find(state.begin(), state.end(), ch) != state.end()) {
		ch++;
	}
	m_finalStates.emplace_back(ch);
	for (const auto& prod : production)
	{
		if (prod.second.size() == 1 && prod.second.at(0) == '@')
		{
			m_finalStates.push_back(m_initialState);
			break;
		}
	}
}

char FiniteAutomaton::getRandomCharacter() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distributie('A', 'Z');
	return static_cast<char>(distributie(gen));
}

//define getters
std::vector<char> FiniteAutomaton::getStates() const {
	return m_states;
}

std::vector<char> FiniteAutomaton::getAlphabet() const {
	return m_alphabet;
}

char FiniteAutomaton::getInitialState() const {
	return m_initialState;
}

std::unordered_map<char, std::unordered_map<char, std::vector<char>>> FiniteAutomaton::getTransition() const {
	return m_transition;
}

std::vector<char> FiniteAutomaton::getFinalStates() const {
	return m_finalStates;
}

