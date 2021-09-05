-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Thief withdrew money at Fifer Street ATM, stole duck at 10:15am at Chamberlin Street courthouse, and exited lot before 10:25am
-- Accomplice received call from thief and purchased place ticket on 7/28/2020 for 7/29/2020 morning flight out of Fiftyville
-- Thief escaped to London on Flight 36

SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';
-- id | year | month | day | street | description
-- 295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

SELECT * FROM interviews WHERE transcript LIKE '%courthouse%' AND month = 7;
--id | name | year | month | day | transcript
--161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;
--id | year | month | day | hour | minute | activity | license_plate
--260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
--261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
--262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
--263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
--264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
--265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
--266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
--267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55

SELECT * FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw';
--id | account_number | year | month | day | atm_location | transaction_type | amount
--246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
--264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
--266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
--267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
--269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
--288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
--313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
--336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

SELECT * FROM bank_accounts JOIN people ON bank_accounts.person_id = people.id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw');
--account_number | person_id | creation_year | id | name | phone_number | passport_number | license_plate
--49610011 | 686048 | 2010 | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
--26013199 | 514354 | 2012 | 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
--16153065 | 458378 | 2012 | 458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
--28296815 | 395717 | 2014 | 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
--25506511 | 396669 | 2014 | 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
--28500762 | 467400 | 2014 | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
--76054385 | 449774 | 2015 | 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
--81061156 | 438727 | 2018 | 438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0

SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (SELECT phone_number FROM bank_accounts JOIN people ON bank_accounts.person_id = people.id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'));
--id | caller | receiver | year | month | day | duration
-- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
--254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
--255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
--279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
--281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54

SELECT * FROM airports JOIN flights ON airports.id = flights.origin_airport_id WHERE city = 'Fiftyville' AND flights.year = 2020 AND flights.month = 7 AND day = 29;
--id | abbreviation | full_name | city | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
--8 | CSF | Fiftyville Regional Airport | Fiftyville | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60 AND caller IN (SELECT phone_number FROM bank_accounts JOIN people ON bank_accounts.person_id = people.id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw' AND account_number IN (SELECT account_number FROM bank_accounts JOIN people ON bank_accounts.person_id = people.id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw') AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND license_plate IN (SELECT license_plate FROM people WHERE passport_number IN (SELECT passport_number FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE flights.id = 36)))))));
