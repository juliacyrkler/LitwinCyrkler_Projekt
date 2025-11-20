-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Lis 20, 2025 at 06:39 PM
-- Wersja serwera: 10.4.32-MariaDB
-- Wersja PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `sklep`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `asortyment`
--

CREATE TABLE `asortyment` (
  `nazwa` varchar(50) NOT NULL,
  `kategoria` varchar(50) NOT NULL,
  `cena` double NOT NULL DEFAULT 0.01,
  `na_magazynie` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `klienci`
--

CREATE TABLE `klienci` (
  `user_id` int(11) NOT NULL,
  `klient_id` int(11) NOT NULL,
  `imie` varchar(25) DEFAULT NULL,
  `nazwisko` varchar(35) DEFAULT NULL,
  `srodki` double DEFAULT 0,
  `pkt_znizkowe` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `pracownicy`
--

CREATE TABLE `pracownicy` (
  `user_id` int(11) DEFAULT NULL,
  `pracownik_id` int(11) NOT NULL,
  `imie` varchar(25) DEFAULT NULL,
  `nazwisko` varchar(35) DEFAULT NULL,
  `typ_pracownika` enum('administrator','menadzer','kasjer') DEFAULT NULL,
  `stawka_godzinowa` double NOT NULL DEFAULT 30.5,
  `godz_w_tyg` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `tranzakcje`
--

CREATE TABLE `tranzakcje` (
  `sprzedajacy` int(11) NOT NULL,
  `kupujacy` int(11) NOT NULL,
  `data_godzina_tranzakcji` datetime DEFAULT NULL,
  `kwota` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `login` varchar(20) DEFAULT NULL,
  `haslo` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `klienci`
--
ALTER TABLE `klienci`
  ADD PRIMARY KEY (`klient_id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indeksy dla tabeli `pracownicy`
--
ALTER TABLE `pracownicy`
  ADD PRIMARY KEY (`pracownik_id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indeksy dla tabeli `tranzakcje`
--
ALTER TABLE `tranzakcje`
  ADD KEY `sprzedajacy` (`sprzedajacy`),
  ADD KEY `kupujacy` (`kupujacy`);

--
-- Indeksy dla tabeli `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `klienci`
--
ALTER TABLE `klienci`
  MODIFY `klient_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `pracownicy`
--
ALTER TABLE `pracownicy`
  MODIFY `pracownik_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `klienci`
--
ALTER TABLE `klienci`
  ADD CONSTRAINT `klienci_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`);

--
-- Constraints for table `pracownicy`
--
ALTER TABLE `pracownicy`
  ADD CONSTRAINT `pracownicy_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`);

--
-- Constraints for table `tranzakcje`
--
ALTER TABLE `tranzakcje`
  ADD CONSTRAINT `tranzakcje_ibfk_1` FOREIGN KEY (`sprzedajacy`) REFERENCES `pracownicy` (`pracownik_id`),
  ADD CONSTRAINT `tranzakcje_ibfk_2` FOREIGN KEY (`kupujacy`) REFERENCES `klienci` (`klient_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
