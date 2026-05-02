/*
 * ATM Simulator — multi-language edition
 * Supported languages: English (default), Hindi, Tamil, Telugu
 * Currency: Indian Rupee (₹)
 *
 * Requires a UTF-8 terminal to display Hindi / Tamil / Telugu strings correctly.
 * On Windows: run  `chcp 65001`  in the console before executing.
/*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <map>

// ── Constants ─────────────────────────────────────────────────────────────────
const double INITIAL_BALANCE  = 5000.0;  // Balance avail
const int    ACCOUNT_PIN      = 1234;
const int    MAX_PIN_ATTEMPTS = 3;
const std::string CURRENCY    = "₹";   // Indian Rupee symbol (UTF-8)

// ── Language string table ─────────────────────────────────────────────────────
//
// Every piece of user-visible text lives here.
// To add a new language: copy one Lang block, change the tag, translate strings.
//
struct Lang {
    std::string name;           // displayed in the language picker

    // Language picker
    std::string selectLang;     // "Select language:"
    std::string defaultNote;    // "(default: English)"

    // PIN screen
    std::string enterPin;
    std::string invalidInput;
    std::string wrongPin;       // "%d attempt(s) remaining" — use with printf-style logic
    std::string cardBlocked;
    std::string welcome;

    // Menu
    std::string menuHeader;
    std::string menuDeposit;
    std::string menuWithdraw;
    std::string menuBalance;
    std::string menuHistory;
    std::string menuExit;
    std::string enterChoice;
    std::string invalidChoice;

    // Transactions
    std::string enterAmount;
    std::string invalidAmount;
    std::string mustBePositive;
    std::string depositOk;      // "Deposited ₹X successfully"
    std::string withdrawOk;
    std::string insufficientFunds;

    // Balance
    std::string currentBalance;

    // History
    std::string historyHeader;
    std::string historyFooter;
    std::string historyDeposit;   // label prefix
    std::string historyWithdraw;
    std::string noHistory;

    // Exit
    std::string goodbye;
};

// ── English ───────────────────────────────────────────────────────────────────
Lang makeEnglish() {
    Lang L;
    L.name            = "English";
    L.selectLang      = "Select language:";
    L.defaultNote     = "(press Enter for English)";
    L.enterPin        = "Enter PIN: ";
    L.invalidInput    = "Invalid input — please enter numbers only.";
    L.wrongPin        = "Incorrect PIN. %d attempt(s) remaining.";
    L.cardBlocked     = "Too many incorrect attempts. Card blocked.";
    L.welcome         = "Access granted. Welcome!";
    L.menuHeader      = "--- ATM MENU ---";
    L.menuDeposit     = "1. Deposit";
    L.menuWithdraw    = "2. Withdraw";
    L.menuBalance     = "3. Check Balance";
    L.menuHistory     = "4. Transaction History";
    L.menuExit        = "5. Exit";
    L.enterChoice     = "Enter choice: ";
    L.invalidChoice   = "Invalid choice — enter 1 to 5.";
    L.enterAmount     = "Enter amount: ";
    L.invalidAmount   = "Invalid amount.";
    L.mustBePositive  = "Amount must be greater than zero.";
    L.depositOk       = "Deposited successfully.";
    L.withdrawOk      = "Withdrawn successfully.";
    L.insufficientFunds = "Insufficient balance.";
    L.currentBalance  = "Current balance: ";
    L.historyHeader   = "--- Transaction History ---";
    L.historyFooter   = "---------------------------";
    L.historyDeposit  = "Deposited: ";
    L.historyWithdraw = "Withdrew:  ";
    L.noHistory       = "No transactions this session.";
    L.goodbye         = "Thank you for using the ATM. Goodbye!";
    return L;
}

// ── Hindi ─────────────────────────────────────────────────────────────────────
Lang makeHindi() {
    Lang L;
    L.name            = "Hindi (हिन्दी)";
    L.selectLang      = "भाषा चुनें:";
    L.defaultNote     = "(डिफ़ॉल्ट: अंग्रेज़ी)";
    L.enterPin        = "PIN दर्ज करें: ";
    L.invalidInput    = "अमान्य इनपुट — कृपया केवल संख्याएँ दर्ज करें।";
    L.wrongPin        = "गलत PIN। %d प्रयास शेष।";
    L.cardBlocked     = "बहुत अधिक गलत प्रयास। कार्ड ब्लॉक हो गया।";
    L.welcome         = "पहुँच प्रदान की गई। आपका स्वागत है!";
    L.menuHeader      = "--- ATM मेनू ---";
    L.menuDeposit     = "1. जमा करें";
    L.menuWithdraw    = "2. निकासी करें";
    L.menuBalance     = "3. शेष राशि जाँचें";
    L.menuHistory     = "4. लेनदेन इतिहास";
    L.menuExit        = "5. बाहर निकलें";
    L.enterChoice     = "विकल्प दर्ज करें: ";
    L.invalidChoice   = "अमान्य विकल्प — 1 से 5 तक दर्ज करें।";
    L.enterAmount     = "राशि दर्ज करें: ";
    L.invalidAmount   = "अमान्य राशि।";
    L.mustBePositive  = "राशि शून्य से अधिक होनी चाहिए।";
    L.depositOk       = "सफलतापूर्वक जमा किया।";
    L.withdrawOk      = "सफलतापूर्वक निकाला।";
    L.insufficientFunds = "अपर्याप्त शेष राशि।";
    L.currentBalance  = "वर्तमान शेष: ";
    L.historyHeader   = "--- लेनदेन इतिहास ---";
    L.historyFooter   = "---------------------";
    L.historyDeposit  = "जमा:    ";
    L.historyWithdraw = "निकासी: ";
    L.noHistory       = "इस सत्र में कोई लेनदेन नहीं।";
    L.goodbye         = "ATM का उपयोग करने के लिए धन्यवाद। अलविदा!";
    return L;
}

// ── Tamil ─────────────────────────────────────────────────────────────────────
Lang makeTamil() {
    Lang L;
    L.name            = "Tamil (தமிழ்)";
    L.selectLang      = "மொழியை தேர்ந்தெடுக்கவும்:";
    L.defaultNote     = "(இயல்பு: ஆங்கிலம்)";
    L.enterPin        = "PIN உள்ளிடவும்: ";
    L.invalidInput    = "தவறான உள்ளீடு — எண்களை மட்டும் உள்ளிடவும்.";
    L.wrongPin        = "தவறான PIN. %d முயற்சிகள் மீதமுள்ளன.";
    L.cardBlocked     = "அதிக தவறான முயற்சிகள். அட்டை தடுக்கப்பட்டது.";
    L.welcome         = "அணுகல் வழங்கப்பட்டது. வரவேற்கிறோம்!";
    L.menuHeader      = "--- ATM பட்டியல் ---";
    L.menuDeposit     = "1. வைப்பு";
    L.menuWithdraw    = "2. திரும்பப் பெறுதல்";
    L.menuBalance     = "3. இருப்பு சரிபார்க்க";
    L.menuHistory     = "4. பரிவர்த்தனை வரலாறு";
    L.menuExit        = "5. வெளியேறு";
    L.enterChoice     = "தேர்வு உள்ளிடவும்: ";
    L.invalidChoice   = "தவறான தேர்வு — 1 முதல் 5 வரை உள்ளிடவும்.";
    L.enterAmount     = "தொகை உள்ளிடவும்: ";
    L.invalidAmount   = "தவறான தொகை.";
    L.mustBePositive  = "தொகை பூஜ்ஜியத்தை விட அதிகமாக இருக்க வேண்டும்.";
    L.depositOk       = "வெற்றிகரமாக வைப்பு செய்யப்பட்டது.";
    L.withdrawOk      = "வெற்றிகரமாக திரும்பப் பெறப்பட்டது.";
    L.insufficientFunds = "போதுமான இருப்பு இல்லை.";
    L.currentBalance  = "தற்போதைய இருப்பு: ";
    L.historyHeader   = "--- பரிவர்த்தனை வரலாறு ---";
    L.historyFooter   = "-------------------------";
    L.historyDeposit  = "வைப்பு:         ";
    L.historyWithdraw = "திரும்பப் பெறல்: ";
    L.noHistory       = "இந்த அமர்வில் பரிவர்த்தனைகள் இல்லை.";
    L.goodbye         = "ATM பயன்படுத்தியதற்கு நன்றி. விடைபெறுகிறோம்!";
    return L;
}

// ── Telugu ────────────────────────────────────────────────────────────────────
Lang makeTelugu() {
    Lang L;
    L.name            = "Telugu (తెలుగు)";
    L.selectLang      = "భాషను ఎంచుకోండి:";
    L.defaultNote     = "(డిఫాల్ట్: ఆంగ్లం)";
    L.enterPin        = "PIN నమోదు చేయండి: ";
    L.invalidInput    = "చెల్లని ఇన్పుట్ — దయచేసి సంఖ్యలు మాత్రమే నమోదు చేయండి.";
    L.wrongPin        = "తప్పు PIN. %d ప్రయత్నాలు మిగిలి ఉన్నాయి.";
    L.cardBlocked     = "చాలా తప్పు ప్రయత్నాలు. కార్డు బ్లాక్ చేయబడింది.";
    L.welcome         = "యాక్సెస్ మంజూరు చేయబడింది. స్వాగతం!";
    L.menuHeader      = "--- ATM మెను ---";
    L.menuDeposit     = "1. డిపాజిట్";
    L.menuWithdraw    = "2. డబ్బు తీసుకోండి";
    L.menuBalance     = "3. బ్యాలెన్స్ తనిఖీ";
    L.menuHistory     = "4. లావాదేవీ చరిత్ర";
    L.menuExit        = "5. నిష్క్రమించు";
    L.enterChoice     = "ఎంపిక నమోదు చేయండి: ";
    L.invalidChoice   = "చెల్లని ఎంపిక — 1 నుండి 5 వరకు నమోదు చేయండి.";
    L.enterAmount     = "మొత్తం నమోదు చేయండి: ";
    L.invalidAmount   = "చెల్లని మొత్తం.";
    L.mustBePositive  = "మొత్తం సున్నా కంటే ఎక్కువగా ఉండాలి.";
    L.depositOk       = "విజయవంతంగా డిపాజిట్ చేయబడింది.";
    L.withdrawOk      = "విజయవంతంగా డబ్బు తీసుకోబడింది.";
    L.insufficientFunds = "సరిపోయే బ్యాలెన్స్ లేదు.";
    L.currentBalance  = "ప్రస్తుత బ్యాలెన్స్: ";
    L.historyHeader   = "--- లావాదేవీ చరిత్ర ---";
    L.historyFooter   = "----------------------";
    L.historyDeposit  = "డిపాజిట్:  ";
    L.historyWithdraw = "డబ్బు తీసుకున్నారు: ";
    L.noHistory       = "ఈ సెషన్‌లో లావాదేవీలు లేవు.";
    L.goodbye         = "ATM ఉపయోగించినందుకు ధన్యవాదాలు. వీడ్కోలు!";
    return L;
}

// ── Helper: format rupee amount ───────────────────────────────────────────────
std::string formatRupees(double amount) {
    std::ostringstream oss;
    oss << CURRENCY << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}

// ── Helper: safe numeric read from cin ───────────────────────────────────────
//   Returns true if a valid number was read, false on bad input.
template<typename T>
bool safeRead(T& value) {
    if (std::cin >> value) return true;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

// ── Language picker ───────────────────────────────────────────────────────────
Lang pickLanguage(const std::vector<Lang>& languages) {
    // The picker itself is always shown in English so the user can read it
    // before they've chosen a language.
    std::cout << "\n=== ATM Language Selection ===\n";
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << (i + 1) << ". " << languages[i].name;
        if (i == 0) std::cout << "  (default)";
        std::cout << "\n";
    }
    std::cout << "Enter number (or press Enter for English): ";

    std::string line;
    std::getline(std::cin >> std::ws, line);   // flush leading whitespace, then read line

    if (line.empty()) return languages[0];     // default: English

    try {
        int choice = std::stoi(line);
        if (choice >= 1 && choice <= static_cast<int>(languages.size())) {
            return languages[choice - 1];
        }
    } catch (...) {}

    std::cout << "Invalid selection — using English.\n";
    return languages[0];
}

// ── Account class ─────────────────────────────────────────────────────────────
class Account {
private:
    double balance;
    int    pin;
    std::vector<std::string> history;

public:
    Account(double b, int p) : balance(b), pin(p) {}

    bool authenticate(int enteredPin) const {
        return enteredPin == pin;
    }

    void deposit(double amount, const Lang& L) {
        if (amount <= 0) { std::cout << L.mustBePositive << "\n"; return; }
        balance += amount;
        history.push_back(L.historyDeposit + formatRupees(amount));
        std::cout << L.depositOk << "  (" << formatRupees(amount) << ")\n";
    }

    void withdraw(double amount, const Lang& L) {
        if (amount <= 0)      { std::cout << L.mustBePositive   << "\n"; return; }
        if (amount > balance) { std::cout << L.insufficientFunds << "\n"; return; }
        balance -= amount;
        history.push_back(L.historyWithdraw + formatRupees(amount));
        std::cout << L.withdrawOk << "  (" << formatRupees(amount) << ")\n";
    }

    void checkBalance(const Lang& L) const {
        std::cout << L.currentBalance << formatRupees(balance) << "\n";
    }

    void printHistory(const Lang& L) const {
        if (history.empty()) { std::cout << L.noHistory << "\n"; return; }
        std::cout << "\n" << L.historyHeader << "\n";
        for (const std::string& entry : history)
            std::cout << "  " << entry << "\n";
        std::cout << L.historyFooter << "\n";
    }
};

// ── ATM class ─────────────────────────────────────────────────────────────────
class ATM {
private:
    Account& acc;

public:
    explicit ATM(Account& a) : acc(a) {}

    void start(const Lang& L) {
        // ── PIN authentication ────────────────────────────────────────────────
        int  attempts      = 0;
        bool authenticated = false;

        while (attempts < MAX_PIN_ATTEMPTS) {
            std::cout << L.enterPin;
            int enteredPin;
            if (!safeRead(enteredPin)) {
                std::cout << L.invalidInput << "\n";
                continue;
            }
            if (acc.authenticate(enteredPin)) { authenticated = true; break; }

            attempts++;
            int remaining = MAX_PIN_ATTEMPTS - attempts;
            if (remaining > 0) {
                char buf[128];
                std::snprintf(buf, sizeof(buf), L.wrongPin.c_str(), remaining);
                std::cout << buf << "\n";
            }
        }

        if (!authenticated) { std::cout << L.cardBlocked << "\n"; return; }
        std::cout << L.welcome << "\n";

        // ── Main menu loop ────────────────────────────────────────────────────
        int choice;
        do {
            std::cout << "\n" << L.menuHeader  << "\n"
                      << L.menuDeposit  << "\n"
                      << L.menuWithdraw << "\n"
                      << L.menuBalance  << "\n"
                      << L.menuHistory  << "\n"
                      << L.menuExit     << "\n"
                      << L.enterChoice;

            if (!safeRead(choice)) {
                std::cout << L.invalidInput << "\n";
                choice = 0;
                continue;
            }

            double amount;
            switch (choice) {
                case 1:
                    std::cout << L.enterAmount;
                    if (!safeRead(amount)) { std::cout << L.invalidAmount << "\n"; break; }
                    acc.deposit(amount, L);
                    break;

                case 2:
                    std::cout << L.enterAmount;
                    if (!safeRead(amount)) { std::cout << L.invalidAmount << "\n"; break; }
                    acc.withdraw(amount, L);
                    break;

                case 3:
                    acc.checkBalance(L);
                    break;

                case 4:
                    acc.printHistory(L);
                    break;

                case 5:
                    std::cout << L.goodbye << "\n";
                    break;

                default:
                    std::cout << L.invalidChoice << "\n";
            }
        } while (choice != 5);
    }
};

// ── main ──────────────────────────────────────────────────────────────────────
int main() {
    // Register all supported languages (English must be first — it's the default)
    std::vector<Lang> languages = {
        makeEnglish(),
        makeHindi(),
        makeTamil(),
        makeTelugu()
    };

    // Step 1: let the user pick a language
    Lang chosenLang = pickLanguage(languages);
    std::cout << "\n";

    // Step 2: run the ATM in the chosen language
    Account userAccount(INITIAL_BALANCE, ACCOUNT_PIN);
    ATM atm(userAccount);
    atm.start(chosenLang);

    return 0;
}
