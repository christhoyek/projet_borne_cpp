# projet_borne

Simulation and control software for an EV charging station (borne).
The system supports two modes: client database management and charging.
It integrates with a smart card reader and a shared-memory hardware simulator
to manage LEDs, buttons, the plug/trap, and the charge generator.

## Features
- Card-based authentication against a local text database
- Interactive client management: add, delete, and modify card holders
- Charging flow with LED feedback, button confirmation, and recovery auth
- Generator state machine for DC/AC control and charge completion

## Project Structure
- `borne.c`: main menu and mode selection loop
- `lecteurcarte.c`: card reading, authentication, and full charge flow
- `baseclient.c`: client database CRUD in `baseclient.txt`
- `Generateur_save.c`: charge process state machine and voltage control
- `voyant.c`: LED control (charge, availability, fault, plug, trap)
- `bouton.c`: charge/stop button access via shared memory
- `prise.c`: plug/trap control

## Build
Requires the shared hardware libs and headers referenced in the Makefile.

```sh
make
```

## Run
```sh
./borne
```

## Client Database Format
The file `baseclient.txt` stores one client per line:

```
<card_number> <name> <surname>
```

## Notes
- The code relies on `memoire_borne`, `donnees_borne`, and `lcarte` APIs.
- The hardware simulator updates shared memory values for LEDs, buttons, and voltages.