// =============================================================================
// CPP_umsteiger.cpp — Installations-Check für die C++-Schulung
//
// Wenn dieses Programm baut und am Ende "ALLES OK" meldet, bauen und laufen
// alle Demos und Übungen der Schulung auf diesem Rechner. Das Projekt benutzt
// exakt dieselben Compiler-Einstellungen wie die Schulung:
// x64, /std:c++latest (C++23), /W4, /permissive-, /utf-8.
//
// Ausführen: CPP_umsteiger.sln öffnen → F5. Die Konsole bleibt am Ende offen.
// =============================================================================

#include "console_utf8.h"   // Windows-Konsole auf UTF-8 — dieselbe Datei wie in der Schulung

#include <version>          // Feature-Test-Makros der Standardbibliothek (__cpp_lib_*)

#include <atomic>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#if defined(__cpp_lib_format)
#  include <format>
#endif
#if defined(__cpp_lib_expected)
#  include <expected>
#endif
#if defined(__cpp_lib_print)
#  include <print>
#endif
#if defined(__cpp_lib_generator)
#  include <generator>
#  include <ranges>
#endif
#if defined(__cpp_lib_math_constants)
#  include <numbers>
#endif

// -----------------------------------------------------------------------------
// Compile-Zeit-Checks mit Klartext-Meldung — ein Verstoß bricht den Build mit
// einer verständlichen Fehlermeldung ab (Fehlerliste in Visual Studio).
// -----------------------------------------------------------------------------
// (Die #error-/static_assert-Texte bleiben ohne Umlaute: die Fehlerliste von
//  Visual Studio zeigt Compiler-Meldungen nicht immer als UTF-8 an.)
#if !defined(_MSC_VER)
#  error "Dieser Check setzt den Microsoft-Compiler (Visual Studio) voraus."
#endif

// /utf-8: Ohne diese Option liest MSVC die Datei in der Windows-ANSI-Codepage;
// aus "ä" (2 Bytes UTF-8) werden dann 2 Fremdzeichen = 4 Bytes + Nullbyte.
static_assert(sizeof(u8"ä") == 3,
    "Quelldatei wird nicht als UTF-8 gelesen: Compiler-Option /utf-8 fehlt "
    "(Projekt -> Eigenschaften -> C/C++ -> Befehlszeile: /utf-8).");

#if _MSVC_LANG < 202002L
#  error "C++20 oder neuer erforderlich: Projekt -> Eigenschaften -> C/C++ -> Sprache -> C++-Sprachstandard: 'Vorschau' (/std:c++latest)."
#endif

// -----------------------------------------------------------------------------
// Was geprüft wird (als Konstanten, damit /W4 keine "constant condition" meldet)
// -----------------------------------------------------------------------------
constexpr bool kVs2022orNewer   = _MSC_VER >= 1930;      // VS 2022 17.0
constexpr bool kVs17_13orNewer  = _MSC_VER >= 1943;      // std::generator
constexpr bool kCppLatest       = _MSVC_LANG > 202002L;  // /std:c++latest
#if defined(_M_X64)
constexpr bool kX64 = true;
#else
constexpr bool kX64 = false;
#endif
#if defined(_DEBUG)
constexpr const char* kConfig = "Debug";
#else
constexpr const char* kConfig = "Release";
#endif

// -----------------------------------------------------------------------------
// Hilfsfunktionen für die Ausgabe
// -----------------------------------------------------------------------------
namespace {

int failures = 0;

// Anzahl der Zeichen (nicht Bytes) eines UTF-8-Strings — für die Ausrichtung,
// damit Umlaute (2 Bytes) die Spalten nicht verschieben.
std::size_t display_width(const std::string& s)
{
    std::size_t n = 0;
    for (unsigned char c : s) if ((c & 0xC0) != 0x80) ++n;   // Folgebytes nicht zählen
    return n;
}

// Eine Zeile der Checkliste: Haken, Bezeichnung, Details/Hinweis.
void line(const std::string& what, bool ok, const std::string& detail)
{
    std::cout << "  " << (ok ? "✓" : "✗") << ' ' << what;
    for (std::size_t i = display_width(what); i < 44; ++i) std::cout << ' ';
    std::cout << detail << '\n';
    if (!ok) ++failures;
}

const char* pick(bool ok, const char* if_ok, const char* if_not) { return ok ? if_ok : if_not; }
std::string pick(bool ok, const std::string& if_ok, const std::string& if_not) { return ok ? if_ok : if_not; }

std::string vs_version(int v)   // v = _MSC_VER
{
    // 1930..1944 = VS 2022 17.0..17.14, ab 1950 = VS 2026 (18.x)
    if (v >= 1950) return "Visual Studio 2026 (18.x), MSVC " + std::to_string(v);
    if (v >= 1930) return "Visual Studio 2022 17." + std::to_string(v - 1930) + ", MSVC " + std::to_string(v);
    return "MSVC " + std::to_string(v) + " — zu alt, Visual Studio 2022 oder neuer installieren";
}

#if defined(__cpp_lib_generator)
std::generator<int> fibonacci()
{
    int a = 0, b = 1;
    while (true) { co_yield a; int t = a + b; a = b; b = t; }
}
#endif

} // namespace

// -----------------------------------------------------------------------------
int main()
{
    std::cout << "=== C++-Schulung: Installations-Check ===\n\n";

    // ---- Compiler & Projekteinstellungen -----------------------------------
    std::cout << "Compiler & Projekteinstellungen\n";
    line("Compiler", kVs2022orNewer, vs_version(_MSC_VER));
    line("Visual Studio 2022 ab 17.13", kVs17_13orNewer,
         pick(kVs17_13orNewer, "ok (Voraussetzung für std::generator)",
                               "zu alt → Visual Studio Installer → „Aktualisieren“"));
    line("Sprachstandard /std:c++latest (C++23)", kCppLatest,
         pick(kCppLatest, "ok, _MSVC_LANG = " + std::to_string(_MSVC_LANG),
                          std::string{"nur C++20 → Projekt → C/C++ → Sprache → „Vorschau“ (/std:c++latest)"}));
    line("Plattform x64", kX64, pick(kX64, "x64", "nicht x64 → in der Symbolleiste „x64“ statt „x86“ wählen"));
    line("Konfiguration", true, kConfig);
    line("Quelltext als UTF-8 (/utf-8)", true, "ok (static_assert bestanden)");

    // ---- Konsole -------------------------------------------------------------
    std::cout << "\nKonsole\n";
    const unsigned cp = GetConsoleOutputCP();
    line("Konsole auf UTF-8 (console_utf8.h)", cp == 65001,
         cp == 65001 ? std::string{"Codepage 65001"}
                     : "Codepage " + std::to_string(cp) + " → Umlaute erscheinen falsch");
    std::cout << "    Testzeile — muss lesbar sein:  ä ö ü ß  →  ✓ ⚠ °C\n";

    // ---- Standardbibliothek (Feature-Test-Makros) ----------------------------
    std::cout << "\nStandardbibliothek\n";
#if defined(__cpp_lib_format)
    line("<format>    std::format", true, std::format("ok ({} + {} = {})", 2, 3, 2 + 3));
#else
    line("<format>    std::format", false, "fehlt → VS 2022 ab 17.2");
#endif
#if defined(__cpp_lib_ranges) && defined(__cpp_lib_span) && defined(__cpp_lib_concepts)
    line("<ranges>, <span>, <concepts>", true, "ok");
#else
    line("<ranges>, <span>, <concepts>", false, "fehlt → C++20 einschalten bzw. Visual Studio aktualisieren");
#endif
#if defined(__cpp_lib_math_constants)
    line("<numbers>   std::numbers::pi", true, "ok (pi = " + std::to_string(std::numbers::pi) + ")");
#else
    line("<numbers>   std::numbers::pi", false, "fehlt → C++20 einschalten bzw. Visual Studio aktualisieren");
#endif
#if defined(__cpp_lib_expected)
    {
        std::expected<int, std::string> e = 42;
        line("<expected>  std::expected   (C++23)", e.has_value() && *e == 42, "ok (VS 2022 ab 17.3)");
    }
#else
    line("<expected>  std::expected   (C++23)", false, "fehlt → VS 2022 ab 17.3 und /std:c++latest");
#endif
#if defined(__cpp_lib_print)
    line("<print>     std::print      (C++23)", true, "ok (VS 2022 ab 17.7)");
#else
    line("<print>     std::print      (C++23)", false, "fehlt → VS 2022 ab 17.7 und /std:c++latest");
#endif
#if defined(__cpp_lib_generator)
    {
        std::string s;
        for (int x : fibonacci() | std::views::take(6)) s += std::to_string(x) + ' ';
        line("<generator> std::generator  (C++23)", s == "0 1 1 2 3 5 ", "ok, fibonacci: " + s);
    }
#else
    line("<generator> std::generator  (C++23)", false, "fehlt → VS 2022 ab 17.13 und /std:c++latest");
#endif

    // ---- Laufzeit --------------------------------------------------------------
    std::cout << "\nLaufzeit\n";
    {
        std::atomic<int> counter{0};
        std::thread t1{[&] { for (int i = 0; i < 1000; ++i) ++counter; }};
        std::thread t2{[&] { for (int i = 0; i < 1000; ++i) ++counter; }};
        t1.join();
        t2.join();
        line("2 Threads gestartet und beendet", counter == 2000, "ok (Zähler = " + std::to_string(counter.load()) + ")");
    }
    {
        namespace fs = std::filesystem;
        const fs::path cwd  = fs::current_path();
        const fs::path file = cwd / "installcheck_tmp.txt";
        bool ok = false;
        {
            std::ofstream out{file};
            ok = static_cast<bool>(out << "hello\n");
        }
        std::error_code ec;
        fs::remove(file, ec);
        line("Arbeitsverzeichnis beschreibbar", ok, (ok ? "" : "NICHT beschreibbar: ") + cwd.string());
    }

    // ---- Ergebnis --------------------------------------------------------------
    std::cout << '\n';
    if (failures == 0) {
        std::cout << "=== ALLES OK — die Schulungsprojekte bauen und laufen auf diesem Rechner. ===\n";
    } else {
        std::cout << "=== " << failures << " Punkt(e) mit ✗ — bitte die Hinweise rechts beachten. ===\n";
    }
    std::cout << "\n(Fenster kann geschlossen werden.)\n";
    return failures == 0 ? 0 : 1;
}
