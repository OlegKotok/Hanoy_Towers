#include "localization.h"

Localizer g_localizer;

Localizer::Localizer() {
    currentLang = GetSystemLanguage();
    LoadStrings();
}

std::string Localizer::GetSystemLanguage() {
    LANGID langId = GetSystemDefaultUILanguage();
    WORD primaryLang = PRIMARYLANGID(langId);
    
    switch (primaryLang) {
        case LANG_GERMAN: return "de";
        case LANG_SPANISH: return "es";
        case LANG_FRENCH: return "fr";
        case LANG_ITALIAN: return "it";
        case LANG_DUTCH: return "nl";
        case LANG_PORTUGUESE: return "pt";
        case LANG_POLISH: return "pl";
        case LANG_ROMANIAN: return "ro";
        case LANG_CZECH: return "cs";
        case LANG_HUNGARIAN: return "hu";
        case LANG_SWEDISH: return "sv";
        case LANG_NORWEGIAN: return "no";
        case LANG_DANISH: return "da";
        case LANG_FINNISH: return "fi";
        case LANG_GREEK: return "el";
        case LANG_BULGARIAN: return "bg";
        case LANG_CROATIAN: return "hr";
        case LANG_SLOVAK: return "sk";
        case LANG_SLOVENIAN: return "sl";
        case LANG_RUSSIAN: return "ru";
        case LANG_UKRAINIAN: return "uk";
        case LANG_ENGLISH: 
        default: return "en";
    }
}

void Localizer::LoadStrings() {
    // English
    strings["en"]["window_title"] = L"Hanoi Towers 2";
    strings["en"]["game_info"] = L"Move all %d rings to the rightmost tower!";
    strings["en"]["win_title"] = L"You won!";
    strings["en"]["win_message"] = L"Congratulations! You solved it in\n%d moves.";
    
    // German
    strings["de"]["window_title"] = L"Türme von Hanoi 2";
    strings["de"]["game_info"] = L"Bewege alle %d Ringe zum rechten Turm!";
    strings["de"]["win_title"] = L"Du hast gewonnen!";
    strings["de"]["win_message"] = L"Glückwunsch! Du hast es in\n%d Zügen geschafft.";
    
    // Spanish
    strings["es"]["window_title"] = L"Torres de Hanoi 2";
    strings["es"]["game_info"] = L"¡Mueve todos los %d anillos a la torre derecha!";
    strings["es"]["win_title"] = L"¡Has ganado!";
    strings["es"]["win_message"] = L"¡Felicidades! Lo resolviste en\n%d movimientos.";
    
    // French
    strings["fr"]["window_title"] = L"Tours de Hanoï 2";
    strings["fr"]["game_info"] = L"Déplacez tous les %d anneaux vers la tour de droite!";
    strings["fr"]["win_title"] = L"Vous avez gagné!";
    strings["fr"]["win_message"] = L"Félicitations! Vous l'avez résolu en\n%d coups.";
    
    // Italian
    strings["it"]["window_title"] = L"Torri di Hanoi 2";
    strings["it"]["game_info"] = L"Sposta tutti i %d anelli alla torre destra!";
    strings["it"]["win_title"] = L"Hai vinto!";
    strings["it"]["win_message"] = L"Congratulazioni! L'hai risolto in\n%d mosse.";
    
    // Dutch
    strings["nl"]["window_title"] = L"Torens van Hanoi 2";
    strings["nl"]["game_info"] = L"Verplaats alle %d ringen naar de rechter toren!";
    strings["nl"]["win_title"] = L"Je hebt gewonnen!";
    strings["nl"]["win_message"] = L"Gefeliciteerd! Je hebt het opgelost in\n%d zetten.";
    
    // Portuguese
    strings["pt"]["window_title"] = L"Torres de Hanói 2";
    strings["pt"]["game_info"] = L"Mova todos os %d anéis para a torre direita!";
    strings["pt"]["win_title"] = L"Você ganhou!";
    strings["pt"]["win_message"] = L"Parabéns! Você resolveu em\n%d movimentos.";
    
    // Polish
    strings["pl"]["window_title"] = L"Wieże Hanoi 2";
    strings["pl"]["game_info"] = L"Przenieś wszystkie %d pierścieni na prawą wieżę!";
    strings["pl"]["win_title"] = L"Wygrałeś!";
    strings["pl"]["win_message"] = L"Gratulacje! Rozwiązałeś to w\n%d ruchach.";
    
    // Romanian
    strings["ro"]["window_title"] = L"Turnurile din Hanoi 2";
    strings["ro"]["game_info"] = L"Mută toate cele %d inele la turnul din dreapta!";
    strings["ro"]["win_title"] = L"Ai câștigat!";
    strings["ro"]["win_message"] = L"Felicitări! Ai rezolvat în\n%d mutări.";
    
    // Czech
    strings["cs"]["window_title"] = L"Hanojské věže 2";
    strings["cs"]["game_info"] = L"Přesuň všech %d kroužků na pravou věž!";
    strings["cs"]["win_title"] = L"Vyhrál jsi!";
    strings["cs"]["win_message"] = L"Gratulujeme! Vyřešil jsi to za\n%d tahů.";
    
    // Hungarian
    strings["hu"]["window_title"] = L"Hanoi tornyai 2";
    strings["hu"]["game_info"] = L"Mozgasd mind a %d gyűrűt a jobb oldali toronyba!";
    strings["hu"]["win_title"] = L"Nyertél!";
    strings["hu"]["win_message"] = L"Gratulálunk! Megoldottad\n%d lépésben.";
    
    // Swedish
    strings["sv"]["window_title"] = L"Hanois torn 2";
    strings["sv"]["game_info"] = L"Flytta alla %d ringar till högra tornet!";
    strings["sv"]["win_title"] = L"Du vann!";
    strings["sv"]["win_message"] = L"Grattis! Du löste det på\n%d drag.";
    
    // Norwegian
    strings["no"]["window_title"] = L"Hanois tårn 2";
    strings["no"]["game_info"] = L"Flytt alle %d ringer til høyre tårn!";
    strings["no"]["win_title"] = L"Du vant!";
    strings["no"]["win_message"] = L"Gratulerer! Du løste det på\n%d trekk.";
    
    // Danish
    strings["da"]["window_title"] = L"Hanois tårne 2";
    strings["da"]["game_info"] = L"Flyt alle %d ringe til højre tårn!";
    strings["da"]["win_title"] = L"Du vandt!";
    strings["da"]["win_message"] = L"Tillykke! Du løste det på\n%d træk.";
    
    // Finnish
    strings["fi"]["window_title"] = L"Hanoin tornit 2";
    strings["fi"]["game_info"] = L"Siirrä kaikki %d rengasta oikeaan torniin!";
    strings["fi"]["win_title"] = L"Voitit!";
    strings["fi"]["win_message"] = L"Onnittelut! Ratkaisit sen\n%d siirrossa.";
    
    // Greek
    strings["el"]["window_title"] = L"Πύργοι του Ανόι 2";
    strings["el"]["game_info"] = L"Μετακινήστε όλους τους %d δακτυλίους στον δεξιό πύργο!";
    strings["el"]["win_title"] = L"Κερδίσατε!";
    strings["el"]["win_message"] = L"Συγχαρητήρια! Το λύσατε σε\n%d κινήσεις.";
    
    // Bulgarian
    strings["bg"]["window_title"] = L"Кули на Ханой 2";
    strings["bg"]["game_info"] = L"Преместете всички %d пръстена в дясната кула!";
    strings["bg"]["win_title"] = L"Спечелихте!";
    strings["bg"]["win_message"] = L"Поздравления! Решихте го за\n%d хода.";
    
    // Croatian
    strings["hr"]["window_title"] = L"Hanojski tornjevi 2";
    strings["hr"]["game_info"] = L"Premjestite svih %d prstenova na desni toranj!";
    strings["hr"]["win_title"] = L"Pobijedili ste!";
    strings["hr"]["win_message"] = L"Čestitamo! Riješili ste za\n%d poteza.";
    
    // Slovak
    strings["sk"]["window_title"] = L"Hanojské veže 2";
    strings["sk"]["game_info"] = L"Presuň všetkých %d krúžkov na pravú vežu!";
    strings["sk"]["win_title"] = L"Vyhral si!";
    strings["sk"]["win_message"] = L"Gratulujeme! Vyriešil si to za\n%d ťahov.";
    
    // Slovenian
    strings["sl"]["window_title"] = L"Hanojski stolpi 2";
    strings["sl"]["game_info"] = L"Premakni vseh %d obročev na desni stolp!";
    strings["sl"]["win_title"] = L"Zmagal si!";
    strings["sl"]["win_message"] = L"Čestitke! Rešil si v\n%d potezah.";
    
    // Russian
    strings["ru"]["window_title"] = L"Башни Ханойские 2";
    strings["ru"]["game_info"] = L"Перенеси все %d колец на правую башню!";
    strings["ru"]["win_title"] = L"Ты выиграл!";
    strings["ru"]["win_message"] = L"Поздравляем! Ты решил игру за\n%d ходов.";
    
    // Ukrainian  
    strings["uk"]["window_title"] = L"Ханойські Вежі 2";
    strings["uk"]["game_info"] = L"Перенеси всі %d кілець на праву вежу!";
    strings["uk"]["win_title"] = L"Ти переміг!";
    strings["uk"]["win_message"] = L"Вітаємо! Ти розв'язав гру за\n%d ходів.";
}

std::wstring Localizer::Get(const std::string& key) {
    if (strings[currentLang].count(key)) {
        return strings[currentLang][key];
    }
    return strings["en"][key];
}

std::string Localizer::GetA(const std::string& key) {
    std::wstring wstr = Get(key);
    int size = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    std::string result(size - 1, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &result[0], size, NULL, NULL);
    return result;
}
