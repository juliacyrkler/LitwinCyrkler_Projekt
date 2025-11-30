-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Lis 30, 2025 at 04:03 PM
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
  `ID` int(11) NOT NULL,
  `nazwa` varchar(50) NOT NULL,
  `kategoria` varchar(50) NOT NULL,
  `cena` double NOT NULL DEFAULT 0.01,
  `na_magazynie` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `asortyment`
--

INSERT INTO `asortyment` (`ID`, `nazwa`, `kategoria`, `cena`, `na_magazynie`) VALUES
(1, 'Kajzerka', 'pieczywo', 0.89, 150),
(2, 'Soplica - cytryna 200ml', 'alkohol', 20, 48),
(3, 'KABANOSY POLSKIE 100G SOKOŁÓW', 'mieso', 8.99, 153),
(4, 'Masło extra z polskiej Mleczarni 82% 200g', 'tluszcz', 3.99, 71),
(5, 'Kawa Mielona CLASSIC Intense Dallmayr 500g', 'napoj', 22.5, 27),
(6, 'Deluxe Fusilli GIGANTI 400g', 'makaron', 4.99, 444),
(7, 'Chleb pszenny', 'pieczywo', 3.5, 40),
(8, 'Bułka kajzerka', 'pieczywo', 0.6, 120),
(9, 'Masło ekstra', 'tłuszcz', 6.2, 25),
(10, 'Ser żółty', 'nabiał', 21.9, 10),
(11, 'Mleko 2%', 'nabiał', 2.8, 60),
(12, 'Szynka wieprzowa', 'mięso', 32.5, 12),
(13, 'Kurczak świeży', 'mięso', 18, 20),
(14, 'Kiełbasa śląska', 'mięso', 27.4, 15),
(15, 'Olej rzepakowy', 'tłuszcz', 7.9, 18),
(16, 'Piwo jasne', 'alkohol', 3.2, 80),
(17, 'Wódka czysta', 'alkohol', 28, 30),
(18, 'Czekolada mleczna', 'słodycze', 4.5, 45),
(19, 'Cukier biały', 'artykuły sypkie', 3.1, 70),
(20, 'Mąka pszenna', 'artykuły sypkie', 3.6, 50),
(21, 'Jajka klas A', 'nabiał', 9.5, 35);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `klienci`
--

CREATE TABLE `klienci` (
  `user_id` int(11) NOT NULL,
  `klient_id` int(11) NOT NULL,
  `imie` varchar(25) NOT NULL,
  `nazwisko` varchar(35) NOT NULL,
  `srodki` double DEFAULT 0,
  `pkt_znizkowe` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `klienci`
--

INSERT INTO `klienci` (`user_id`, `klient_id`, `imie`, `nazwisko`, `srodki`, `pkt_znizkowe`) VALUES
(3, 1, 'Antoni', 'Nabzdyk', 0, 0),
(8, 32, 'Jan', 'Kowalski', 120.5, 120),
(9, 33, 'Anna', 'Nowak', 60, 45),
(10, 34, 'Piotr', 'Wiśniewski', 50.75, 230),
(11, 35, 'Katarzyna', 'Wójcik', 80.4, 60),
(12, 36, 'Michał', 'Kaczmarek', 12.2, 300),
(13, 37, 'Agnieszka', 'Mazur', 10, 10),
(14, 38, 'Tomasz', 'Zieliński', 19.99, 180),
(15, 39, 'Monika', 'Kamińska', 430.8, 35),
(16, 40, 'Paweł', 'Lewandowski', 50000, 500),
(17, 41, 'Magdalena', 'Dąbrowska', 75.3, 55),
(18, 42, 'Marcin', 'Pawlak', 140.1, 90),
(19, 43, 'Natalia', 'Michalska', 620.7, 40),
(20, 44, 'Robert', 'Król', 231, 200),
(21, 45, 'Karolina', 'Wieczorek', 300, 15),
(22, 46, 'Daniel', 'Jabłoński', 100.6, 350);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `pracownicy`
--

CREATE TABLE `pracownicy` (
  `user_id` int(11) NOT NULL,
  `pracownik_id` int(11) NOT NULL,
  `imie` varchar(25) NOT NULL,
  `nazwisko` varchar(35) NOT NULL,
  `typ_pracownika` enum('administrator','menadzer','kasjer') NOT NULL,
  `stawka_godzinowa` double NOT NULL DEFAULT 30.5,
  `godz_w_tyg` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `pracownicy`
--

INSERT INTO `pracownicy` (`user_id`, `pracownik_id`, `imie`, `nazwisko`, `typ_pracownika`, `stawka_godzinowa`, `godz_w_tyg`) VALUES
(1, 1, 'Julia', 'Cyrkler', 'administrator', 1000, 1),
(2, 2, 'Laura', 'Litwin', 'administrator', 1, 100),
(4, 3, 'Zbigniew', 'Ziobro', 'kasjer', 30.5, 35),
(5, 4, 'Magdalena', 'Kłosowska', 'kasjer', 30, 0),
(6, 5, 'Anna', 'Adamek', 'kasjer', 30.5, 40),
(7, 6, 'Sean', 'Combs', 'menadzer', 420, 69);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `transakcje`
--

CREATE TABLE `transakcje` (
  `sprzedajacy` int(11) NOT NULL,
  `kupujacy` int(11) NOT NULL,
  `data_godzina_transakcji` datetime DEFAULT NULL,
  `kwota` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `login` varchar(25) NOT NULL,
  `haslo` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `login`, `haslo`) VALUES
(1, 'Julia', 'Cyrkler'),
(2, 'Laura', 'Litwin'),
(3, 'Antoni', 'Nabzdyk'),
(4, 'Kasjer1', 'haslo1'),
(5, 'Kasjer2', 'haslo2'),
(6, 'Kasjer3', 'haslo3'),
(7, 'Menadzer1', 'haslo123'),
(8, 'jankowalski', 'haslo123'),
(9, 'annanowak', 'anna2024'),
(10, 'piotrwisnia', 'piotrpass'),
(11, 'kasiaw', 'kasia321'),
(12, 'michalk', 'michal!@#'),
(13, 'agniecha', 'agnieszka1'),
(14, 'tomekz', 'tomek2023'),
(15, 'monikak', 'monika99'),
(16, 'pawel_lewy', 'pawelpass'),
(17, 'magdad', 'magda777'),
(18, 'marcinp', 'marcin123'),
(19, 'natalia_m', 'nata2024'),
(20, 'robertk', 'robert88'),
(21, 'karolinka', 'karo321'),
(22, 'danielj', 'daniel000');

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `asortyment`
--
ALTER TABLE `asortyment`
  ADD PRIMARY KEY (`ID`);

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
-- Indeksy dla tabeli `transakcje`
--
ALTER TABLE `transakcje`
  ADD KEY `sprzedajacy` (`sprzedajacy`),
  ADD KEY `kupujacy` (`kupujacy`);

--
-- Indeksy dla tabeli `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `login` (`login`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `asortyment`
--
ALTER TABLE `asortyment`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;

--
-- AUTO_INCREMENT for table `klienci`
--
ALTER TABLE `klienci`
  MODIFY `klient_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=47;

--
-- AUTO_INCREMENT for table `pracownicy`
--
ALTER TABLE `pracownicy`
  MODIFY `pracownik_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

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
-- Constraints for table `transakcje`
--
ALTER TABLE `transakcje`
  ADD CONSTRAINT `transakcje_ibfk_1` FOREIGN KEY (`sprzedajacy`) REFERENCES `pracownicy` (`pracownik_id`),
  ADD CONSTRAINT `transakcje_ibfk_2` FOREIGN KEY (`kupujacy`) REFERENCES `klienci` (`klient_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;