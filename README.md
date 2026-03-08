# Excel-Cpp-Calculation-Engine

## Overview
A high-performance calculation engine developed in C++ to optimize financial analysis workflows. This project was engineered to replace slow, legacy VBA-based Excel functions, reducing calculation latency from seconds to near-instantaneous execution.

## The Challenge
* **Performance Bottlenecks:** Users at Constância Investimentos faced delays of up to 50 seconds when refreshing complex financial derivatives analysis spreadsheets.
* **64-bit Interoperability:** Previous attempts to port legacy VBA code to 64-bit Excel environments lacked documentation and suffered from integration failures.
* **Maintainability:** The solution required high robustness without relying on heavy external financial libraries.

## The Solution
* **Native C++ Architecture:** Re-implemented business logic in C++ to achieve deterministic execution and minimal memory footprint.
* **64-bit Compatibility:** Successfully resolved deep integration challenges between Windows DLLs and the Excel API, overcoming limited official documentation.
* **Stateless Design:** Developed as a stateless engine to ensure thread-safety and rapid responses during intensive spreadsheet recalculations.
* **Interface Optimization:** Implemented seamless range-reading and writing protocols to enhance user interface responsiveness.

## Key Technical Achievements
* **Performance:** Eliminated calculation lag, enabling real-time financial modeling within MS Excel.
* **Reverse Engineering:** Successfully ported and modernized legacy business logic from VBA to C++.
* **Compatibility:** Fully compliant with MS Excel 64-bit architecture.

## Technologies
* Language: C++
* Platform: Windows / MS Excel API
* Architecture: DLL-based calculation engine
