# Tamagotchi

Progetto Extra Points del corso di [Architetture dei Sistemi di Elaborazione](https://didattica.polito.it/pls/portal30/gap.pkg_guide.viewGap?p_cod_ins=02GOLOV&p_a_acc=2020&p_header=S&p_lang=IT&multi=N) e liberamente ispirato a Pacman. Sono stati utilizzati i seguenti moduli:
- LCD
- Timer
- Joystick

Per potere eseguire il codice, è sufficiente clonare la repository ed avviare il file sample.uvprojx con [Keil µVision](https://www2.keil.com/mdk5/uvision/) 5.37

## Animazioni
Per animare il *pet* ho creato frame per frame delle immagini con [Figma](https://www.figma.com/file/FZPupS7nCecA4BbI6mYKPb/ASE---LandTiger?node-id=0%3A1&t=BSqibJQh62oJFCR7-1), e le ho poi convertite in array di interi *uint16_t* per mezzo di [un plugin](https://github.com/MrPozor/gimp_export565array) per [GIMP](https://www.gimp.org/)