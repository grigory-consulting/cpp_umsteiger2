# C++-Schulung — Installations-Check (CPP_umsteiger)

Bitte **vor der Schulung** einmal durchlaufen lassen (5 Minuten). Wenn am Ende
`ALLES OK` steht, bauen und laufen alle Übungen und Demos der Schulung auf Ihrem
Rechner — das Projekt verwendet exakt dieselben Compiler-Einstellungen.

## Voraussetzungen

- **Windows 10/11, 64 Bit**
- **Visual Studio 2022 (Version 17.13 oder neuer)** oder Visual Studio 2026 —
  Community Edition reicht (kostenlos: <https://visualstudio.microsoft.com/de/vs/community/>)
- Beim Installieren die Workload **„Desktopentwicklung mit C++"** ankreuzen
  (nachträglich: *Visual Studio Installer → Ändern*)

Version prüfen: Visual Studio → *Hilfe → Info*. Steht dort 17.12 oder kleiner:
*Visual Studio Installer → Aktualisieren*.

## Ablauf

1. Projekt herunterladen: oben **Code → Download ZIP** (oder `git clone`) und an einen
   beliebigen lokalen Ort entpacken — nicht auf ein Netzlaufwerk.
2. **`CPP_umsteiger.sln` doppelklicken.** Erscheint eine Sicherheitsabfrage („Vertrauen Sie diesem
   Projekt?") → bestätigen. Erscheint „Projekte neu ausrichten" → OK.
3. Oben in der Symbolleiste muss **`x64`** stehen (nicht `x86`), Konfiguration `Debug` oder `Release` — egal.
4. **F5** drücken (oder *Debuggen → Debugging starten*).
5. Es öffnet sich ein Konsolenfenster mit einer Checkliste. Erwartet:

```
=== C++-Schulung: Installations-Check ===

Compiler & Projekteinstellungen
  ✓ Compiler                                    Visual Studio 2022 17.14, MSVC 1944
  ✓ Visual Studio 2022 ab 17.13                 ok (Voraussetzung für std::generator)
  ✓ Sprachstandard /std:c++latest (C++23)       ok, _MSVC_LANG = 202400
  ✓ Plattform x64                               x64
  ✓ Konfiguration                               Debug
  ✓ Quelltext als UTF-8 (/utf-8)                ok (static_assert bestanden)

Konsole
  ✓ Konsole auf UTF-8 (console_utf8.h)          Codepage 65001
    Testzeile — muss lesbar sein:  ä ö ü ß  →  ✓ ⚠ °C

Standardbibliothek
  ✓ <format>    std::format                     ok (2 + 3 = 5)
  ✓ <ranges>, <span>, <concepts>                ok
  ✓ <numbers>   std::numbers::pi                ok (pi = 3.141593)
  ✓ <expected>  std::expected   (C++23)         ok (VS 2022 ab 17.3)
  ✓ <print>     std::print      (C++23)         ok (VS 2022 ab 17.7)
  ✓ <generator> std::generator  (C++23)         ok, fibonacci: 0 1 1 2 3 5

Laufzeit
  ✓ 2 Threads gestartet und beendet             ok (Zähler = 2000)
  ✓ Arbeitsverzeichnis beschreibbar             C:\...\CPP_umsteiger

=== ALLES OK — die Schulungsprojekte bauen und laufen auf diesem Rechner. ===
```

6. Bitte auch die **Testzeile** ansehen: `ä ö ü ß → ✓ ⚠ °C` muss genau so lesbar sein.
   (Sieht sie wie `Ã¤` oder `├╢` aus, bitte ein Bildschirmfoto mitbringen.)

## Wenn etwas nicht klappt

| Symptom | Ursache / Lösung |
|---|---|
| Fehlerliste: `error C1189: #error ... C++20 oder neuer erforderlich` | Projekt → Eigenschaften → C/C++ → Sprache → C++-Sprachstandard: **„Vorschau … (/std:c++latest)"** |
| Fehlerliste: `static_assert failed: 'Quelldatei wird nicht als UTF-8 gelesen ...'` | Projekt → Eigenschaften → C/C++ → Befehlszeile → Zusätzliche Optionen: `/utf-8` |
| `✗ Visual Studio 2022 ab 17.13` bzw. `✗ <generator>` | Visual Studio Installer → **Aktualisieren** (Version ≥ 17.13) |
| `✗ Sprachstandard` | wie oben: C++-Sprachstandard auf „Vorschau" (/std:c++latest) |
| `✗ Plattform x64` | Symbolleiste: Plattform von `x86` auf **`x64`** umstellen |
| „Das Windows SDK ... wurde nicht gefunden" / Toolset v143 fehlt | Visual Studio Installer → Ändern → Workload **Desktopentwicklung mit C++** installieren |
| Konsole zeigt `Ã¤` statt `ä` | Bildschirmfoto mitbringen — wir klären das in der Schulung (Codepage/Schriftart) |
| Konsole schließt sofort | *Extras → Optionen → Debuggen → Allgemein → „Konsole automatisch schließen …" abwählen* oder mit **Strg+F5** starten |

Bei allem anderen: Inhalt des Fensters **Ausgabe (Erstellen)** kopieren und mitschicken.

## Was der Check abdeckt

| Prüfpunkt | Wofür es in der Schulung gebraucht wird |
|---|---|
| `/std:c++latest`, `<format>`, `<ranges>`, `<span>`, `<concepts>`, `<numbers>` | alle Demos und Übungen |
| `<expected>`, `<print>` | Kapitel „Modern C++ (C++23)" |
| `<generator>` (VS ≥ 17.13) | Kapitel „Coroutines" |
| Threads | Kapitel „Multithreading" |
| `/utf-8` + Konsole UTF-8 | alle (Umlaute in den Ausgaben) |
| Arbeitsverzeichnis beschreibbar | RAII-Übung (temporäre Datei anlegen) |
