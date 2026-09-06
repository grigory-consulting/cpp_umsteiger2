// =============================================================================
// console_utf8.h
//
// Zweck        : Windows-Konsole auf UTF-8 umstellen, damit Umlaute und
//                Sonderzeichen (ö, ä, ü, ß, °, →, ✓) in der Ausgabe korrekt
//                erscheinen. Die Windows-Konsole benutzt sonst die alte
//                OEM-Codepage (850/437) und zeigt für "ö" etwa "├╢".
//
// Verwendung   : #include "console_utf8.h" — mehr nicht. Ein statisches Objekt
//                setzt die Codepage, bevor main() läuft (Static Initialization).
//
// Hinweis      : Die Quelldateien sind UTF-8 kodiert. Damit MSVC sie auch so
//                liest, ist im Visual-Studio-Projekt die Option /utf-8 gesetzt.
//                Unter Linux/macOS (gcc/clang, CMake) ist diese Datei ein No-op:
//                dort ist UTF-8 ohnehin Standard.
// =============================================================================
#pragma once

#if defined(_WIN32)

#  ifndef NOMINMAX
#    define NOMINMAX                 // windows.h soll min()/max() nicht als Makros definieren
#  endif
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN      // schlanker Include, reicht für die Konsolen-API
#  endif
#  include <windows.h>

namespace {

// RAII-Muster im Kleinen: Konstruktor erledigt die Arbeit, ein statisches
// Objekt sorgt dafür, dass er vor main() ausgeführt wird.
struct ConsoleUtf8Init {
    ConsoleUtf8Init() noexcept
    {
        SetConsoleOutputCP(CP_UTF8);     // Ausgabe (std::cout)
        SetConsoleCP(CP_UTF8);           // Eingabe (std::cin)
    }
};

const ConsoleUtf8Init console_utf8_init_{};

} // namespace

#endif // _WIN32
