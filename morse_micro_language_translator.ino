int buttonPin = 2;
int speakerPin = 3;
int ledPin = 4;

int soundSpeed = 1;
int soundFrequency = 100;
// https://en.wikipedia.org/wiki/Morse_code#Representation.2C_timing_and_speeds
int durationDot = 150;
int durationDash = durationDot * 3;
int durationIntraCharacterGap = durationDot;
int durationLetterSpace = durationDot * 3;
int durationWordSpace = durationDot * 7;
int durationStopOnTime = durationDot * 16;
int durationDotDashMean = (durationDash + durationDot) / 2;
// 
bool isPressedButton = false;
String query = "";
String found = "- ..- -    - -"; // L'Homme de l'intérieur
String lastFound = "";
long int timeCurrent = 0;
long int timeSignal = 0;
long int timeToPlayNextFoundCode = 0;
long int buttonDowntime = 0;
long int buttonUptime = 0;

// https://en.wiktionary.org/wiki/Wiktionary:Frequency_lists
// russian translit to italiano vocabulary
const PROGMEM char vocabulary[] = "i|e||v|in||ne|non||na|su||ia|io||byt|essere||on|egli||s|con||chto|che||a|e||po|per||eto|questo||ona|lei||etot|questo||k|a||no|ma||oni|sono||my|abbiamo||kak|come||iz|da||u|si||kotoryi|che||to|allora||za|per||svoi|ilчт||o|su||ves|tutto||god|anno||ot|da||tak|cosiо|||||dlia|per||ty|tu||je|stesso||vse|tutti||tot|lo||moch|potere||vy|si||chelovek|uomo||takoi|tale||ego|il suo||skazat|dire||tolko|solo||ili|o||esce|altri||by|sarebbe||sebia|te||odin|uno||kak|come||uje|gia||do|fino a||vremia|tempo||esli|se||sam|stesso||kogda|quando||drugoi|altro||vot|ecco||govorit|parlare||nash|il nostro||moi|il mio||znat|sapere||stat|diventare||pri|quando||chtoby|per||delo|il caso||jizn|la vita||kto|chi||pervyi|il primo||ochen|molto||dva|due||den|giorno||ee|il suo||novyi|nuovo||ruka|mano||daje|anche||vo|in||so|con||raz|volte||gde|dove||tam|li||pod|sotto||mojno|e possibile||nu|beh||kakoi|quale||posle|dopo||ih|loro||rabota|lavoro||bez|senza||samyi|piu||potom|poi||nado|bisogna||hotet|desiderare||li|se||slovo|la parola||idti|andare||bolshoi|grande||doljen|deve||mesto|posto||imet|avere||nichto|niente||to|allora||seichas|ora||tut|qui||lico|il volto||kajdyi|ogni||drug|dall||net|no||teper|ora||ni|ne||glaz|occhio||toje|anche||togda|allora||videt|vedere||vopros|domanda||cherez|attraverso||da|si||zdes|qui||dom|casa||da|si||potomu|perche||storona|lato||kakoi-to|una sorta di||dumat|pensare||sdelat|fare||strana|paese||jit|vivere||chem|di||mir|il mondo||ob|di||poslednii|ultimo||sluchai|il caso||golova|testa||bolee|piu||delat|fare||chto-to|qualcosa||smotret|guarda||rebenok|il bambino||prosto|basta||konechno|naturalmente||sila|forza||rossiiskii|russia||konec|fine||pered|prima di||neskolko|piu||vid|vista||sistema|sistema||vsegda|sempre||rabotat|lavorare||mejdu|tra||tri|tre||net|no||poniat|capire||poiti|andare||chast|parte||sprosit|chiedere||gorod|la citta||dat|dare||takje|anche||nikto|nessuno||ponimat|capire||poluchit|ottenere||otnoshenie|atteggiamento||lish|solo||vtoroi|la seconda||imenno|esattamente||vash|il||hotia|anche se||ni|ne||sidet|sedersi||nad|sopra||jenscina|donna||okazatsia|essere||russkii|italiano||odin|uno||vziat|prendere||priiti|venire||iavliatsia|essere||dengi|soldi||pochemu|perche||vdrug|improvvisamente||liubit|amare||stoit|costare||pochti|quasi||zemlia|terreno||obscii|comune||ved|perche||mashina|la macchina||odnako|tuttavia||srazu|subito||horosho|bene||voda|acqua||otec|il padre||vysokii|alto||ostatsia|rimanere||vyiti|uscire||mnogo|un sacco di||problema|il problema||nachat|iniziare||horoshii|buona||chas|ora||eto|questo||segodnia|oggi||pravo|il diritto di||sovsem|tutto||noga|gamba||schitat|considerato||glavnyi|principale||reshenie|la soluzione||uvidet|vedere||dver|porta||kazatsia|sembrare||obraz|immagine||pisat|scrivere||istoriia|la storia||luchshii|migliore||vlast|il potere||zakon|la legge||vse|tutti||voina|la guerra||bog|dio||golos|la voce||naiti|trovare||poetomu|quindi||stoiat|stare||voobsce|in generale||tysiacha|mille||bolshe|di piu||vmeste|insieme||malenkii|piccolo||kniga|il libro||nekotoryi|certo||reshit|risolvere||liuboi|qualsiasi||vozmojnost|la possibilita di||rezultat|il risultato||noch|notte||stol|buffet||nikogda|mai||imia|il nome||oblast|area||molodoi|il giovane||proiti|passare||naprimer|ad esempio||statia|articolo||ono|e||chislo|il numero di||kompaniia|azienda||pro|pro||gosudarstvennyi|codice||polnyi|completo||priniat|prendere||narod|il popolo||nikakoi|nessun||sovetskii|sovietica||jena|la moglie||nastoiascii|il presente||vsiakii|ogni||gruppa|il gruppo||razvitie|lo sviluppo di||process|il processo di||sud|la corte||davat|dare||otvetit|rispondi||staryi|il vecchio||uslovie|la condizione||tvoi|il tuo||poka|fino a quando||sredstvo|lo strumento||pomnit|da ricordare||nachalo|inizio||jdat|aspettare||svet|la luce||pora|e il momento di||put|il percorso||dusha|anima||kuda|dove||nujno|bisogno di||raznyi|diverso||nujnyi|giusto||uroven|il livello di||inoi|altro||forma|la forma||sviaz|comunicazione||uj|cosi||minuta|minuto||krome|oltre||nahoditsia|essere||opiat|ancora una volta||mnogii|многий||belyi|bianco||sobstvennyi|proprio||ulica|via||chernyi|nero||napisat|scrivere||vecher|la serata||snova|di nuovo||osnovnoi|principale||kachestvo|qualita||mysl|il pensiero||doroga|la strada||mat|la madre||deistvie|azione||mesiac|mese||ostavatsia|rimanere||gosudarstvo|governo||iazyk|la lingua||liubov|amore||vzgliad|parere||mama|mamma||igrat|giocare||dalekii|lontano||lejat|mentire||nelzia|non e possibile||vek|un secolo di||shkola|la scuola||podumat|pensare||uiti|andare via||cel|obiettivo||sredi|tra||obscestvo|la societa||posmotret|vedi||deiatelnost|attivita||organizaciia|organizzazione||kto-to|qualcuno||vernutsia|tornare||prezident|il presidente||komnata|sala||poriadok|ordine||moment|momento||teatr|teatro||sledovat|a seguire||chitat|leggere||pismo|lettera||podobnyi|simile||sleduiuscii|il seguente||utro|mattina||osobenno|in particolare||pomosc|aiuto||situaciia|la situazione||rol|il ruolo||byvat|s'||hodit|camminare||rubl|rouble||nachinat|iniziare||poiavitsia|apparire||smysl|significato||sostoianie|lo stato||nazyvat|chiamare||riadom|vicino||kvartira|appartamento||nazad|fa||ravnyi|uguale||iz-za|a causa di||organ|organo||vnimanie|attenzione||telo|il corpo||trud|lavoro||priitis|obbligato||hotetsia|voglia||syn|il figlio||mera|misura||piat|cinque||smert|la morte||jivoi|dal vivo||rynok|il mercato||programma|il programma||zadacha|il compito di||predpriiatie|impresa||izvestnyi|noto||okno|la finestra||vesti|piombo||sovershenno|completamente||voennyi|militare||razgovor|la conversazione||pokazat|visualizza||pravitelstvo|il governo||vajnyi|importante||semia|la famiglia||velikii|grande||proizvodstvo|produzione||prostoi|semplice||znachit|significa||tretii|il terzo||skolko|quanti||ogromnyi|enorme||davno|tempo fa||politicheskii|politico||informaciia|informazioni||deistvitelno|davvero||polojenie|posizione||postavit|mettere||boiatsia|paura||nakonec|infine||centr|centro||proishodit|avvenire||otvet|la risposta||muj|marito||avtor|autore||vse-taki|ancora||stena|parete||suscestvovat|esistere||daje|anche||interes|di interesse||stanovitsia|diventare||federaciia|la federazione||pravilo|la regola||oba|entrambi||chasto|spesso||moskovskii|mosca||upravlenie|gestione||slyshat|sentire||bystro|veloce||smoch|poter||zametit|notare||kak-to|come qualcosa di||mujchina|uomo||dolgo|a lungo||pravda|la verita||ideia|idea||partiia|partito||inogda|a volte||ispolzovat|utilizzare||pytatsia|cercare di||gotovyi|pronto||chut|poco||zachem|perche||predstavit|immaginare||chuvstvovat|sentire||sozdat|creare||sovet|il consiglio||schet|il conto||serdce|il cuore||dvijenie|il movimento||vesc|cosa||material|materiale||nedelia|settimana||chuvstvo|il senso di||zatem|quindi||dannyi|questo||zanimatsia|di impegnarsi||prodoljat|continuare a||krasnyi|rosso||glava|capitolo||ko|a||slushat|ascoltare||nauka|la scienza||uznat|imparare||riad|una serie di||gazeta|il giornale||prichina|il motivo||protiv|contro||plecho|spalla||sovremennyi|moderno||cena|prezzo||plan|il piano di||priehat|arrivare||rech|si||chetyre|quattro||otvechat|rispondere||tochka|il punto di||osnova|la base||tovarisc|il compagno||kultura|cultura||slishkom|troppo||rasskazyvat|raccontare||vpolne|e||dalee|via||rasskazat|raccontare||dannye|i dati||predstavliat|rappresentare||mnenie|opinione||socialnyi|sociale||okolo|circa||dokument|il documento||institut|istituto||hod|il colpo||brat|prendere||zabyt|dimenticare||proekt|il progetto||rannii|anticipato||vstrecha|incontro||osobyi|speciale||celyi|una||direktor|il direttore||provesti|trascorrere||spat|dormire||plohoi|cattivo||mojet|puo||vprochem|del resto||silnyi|forte||navernoe|probabilmente||skoryi|imminente||ved|perche||srok|il periodo di||palec|dito||opyt|esperienza||pomoch|aiutare||bolshe|di piu||prihodit|venire||slujba|il servizio||krupnyi|grande||vnutrennii|interno||prosit|chiedere||vspomnit|ricordare||otkryt|apri||privesti|portare||sudba|il destino||poka|fino a quando||devushka|la ragazza||poskolku|perche||ochered|coda||les|la foresta||pust|lasciate che||ekonomicheskii|economica||ostavit|lasciare||pravyi|a destra||sostav|composizione||slovno|come||federalnyi|federale||sprashivat|chiedi||prinimat|prendere||chlen|membro||iskat|cercare||blizkii|vicino||kolichestvo|il numero di||pohojii|simile||sobytie|evento||obekt|oggetto||zal|sala||sozdanie|la creazione di||voiti|entrare||razlichnyi|differente||znachenie|il valore||nazvat|chiamare||dostatochno|abbastanza||period|il periodo di||hot|anche se||shag|passo||neobhodimyi|necessario||uspet|il tempo di||proizoiti|accadere||brat|il fratello||iskusstvo|arte||edinstvennyi|unico||legkii|facile||struktura|la struttura||vyhodit|uscire||nomer|camera||predlojit|offrire||primer|esempio||pit|bere||issledovanie|la ricerca||grajdanin|cittadino||gliadet|guardo||chelovecheskii|dell'uomo||igra|il gioco||nachalnik|capo||sei|questo||rost|la crescita||ehat|andare||mejdunarodnyi|||tema|il tema||princip|il principio di||dorogoi|caro||popast|entrare||desiat|dieci||nachatsia|iniziare||verit|credere||metod|il metodo||tip|tipo di||film|il film||nebolshoi|piccolo||derjat|tenere||libo|o||pozvoliat|permettere||krai|bordo||mestnyi|locale||menee|meno||gost|ospite||kupit|comprare||uhodit|uscire||sobiratsia|riunirsi||vozduh|aria||tuda|li||otnositsia|trattare||byvshii|ex||trebovat|richiedere||harakter|la natura||borba|la lotta||ispolzovanie|uso di||kstati|a proposito||podoiti|avvicinarsi||razmer|dimensione||udatsia|riesce a||obrazovanie|istruzione||poluchat|ricevere||malchik|il ragazzo||krov|il sangue||raion|regione||nebo|il cielo||amerikanskii|americano||armiia|esercito||klass|classe||predstavitel|rappresentante||uchastie|la partecipazione||devochka|la ragazza||politika|politica||snachala|prima||geroi|eroe||kartina|il quadro||shirokii|una vasta||dollar|il dollaro||spina|spin||territoriia|il territorio||mirovoi|mondiale||pol|il pavimento||tiajelyi|pesante||dovolno|piuttosto||pole|campo||j|stazione||izmenenie|modifica||umeret|morire||bolee|piu||napravlenie|la direzione||risunok|figura||techenie|per||vozmojnyi|possibile||cerkov|la chiesa||bank|banca||otdelnyi|separato||srednii|la media||krasivyi|bella||scena|la scena||naselenie|la popolazione||bolshinstvo|la maggior parte||sest|prendere||dvadcat|venti||sluchitsia|accadere||muzyka|musica||korotkii|breve||pravda|la verita||prohodit|terra||sostavliat|essere||svoboda|la liberta||pamiat|la memoria||prihoditsia|rappresentano||prichem|e||komanda|la squadra||ustanovit|installare||soiuz|unione||budto|se||podniat|sollevare||vrach|il medico||sereznyi|serio||dogovor|contratto||staratsia|cercare di||umet|essere in grado di||vstat|alzarsi||derevo|albero||interesnyi|interessante||fakt|fatto||dobryi|gentile||vsego|tutto||hoziain|ospite||nacionalnyi|nazionale||odnajdy|una volta||dlinnyi|lungo||priroda|natura||domoi|a casa||strashnyi|terribile||proshlyi|scorso||budto|se||obscestvennyi|pubblico||ugol|angolo||chtob|per||telefon|telefono||poziciia|posizione||provodit|tenere||skoro|presto||naibolee|piu||dvor|cortile||obychno|di solito||brosit|smettere di||razve|isnt||pisatel|scrittore||samolet|aereo||obem|il volume||daleko|lontano||rod|genere||solnce|il sole||vera|la fede||bereg|riva||spektakl|spettacolo||firma|ditta||sposob|un modo per||zavod|fabbrica||cvet|colore||trudno|difficile||jurnal|la rivista||rukovoditel|direttore di||specialist|esperto||vozmojno|forse||detskii|bambini||tochno|esattamente||obiasnit|spiegare||ocenka|il punteggio||edinyi|unico||sniat|togliere||opredelennyi|certo||nizkii|basso||nravitsia|piacere||uslyshat|sentire||region|regione||sviazat|collegare||pesnia|la canzone||procent|la percentuale di||roditel|il genitore||pozvolit|permettere||chujoi|qualcun altro||more|mare||strannyi|strano||trebovanie|requisito||chistyi|puro||vesma|molto||kakoi-nibud|qualche||osnovanie|base||polovina|la meta||poehat|andare||polojit|mettere||vhodit|entrare||legko|facile||pozdnii|brunch||roman|il romanzo||krug|cerchio||analiz|analisi||stihi|poesie||avtomobil|auto||specialnyi|speciale||ekonomika|economia||literatura|poesia||bumaga|carta||vmesto|invece||vpervye|per la prima volta||vidno|visto||nauchnyi|scientifico||okazyvatsia|assolti||poet|il poeta||pokazyvat|mostra||stepen|il grado di||vyzvat|chiamare||kasatsia|toccare||gospodin|signor||nadejda|la speranza||slojnyi|complesso||vokrug|intorno||predmet|oggetto||otmetit|notare||zaiavit|dichiarare||variant|opzione||ministr|il ministro||otkuda|localita||realnyi|reale||granica|il confine||deistvovat|agire||duh|lo spirito||model|modello||operaciia|operazione||para|coppia||son|il sonno||nemnogo|un po ' di||nazvanie|titolo||um|la mente||povod|scusa||starik|il vecchio||sposobnyi|in grado di||malo|poco||million|un milione di||malyi|piccolo||starshii|senior||uspeh|successo||prakticheski|praticamente||poluchitsia|a finire||lichnyi|personale||schaste|la felicita||neobhodimo|e necessario||svobodnyi|libero||rebiata|ragazzi||obychnyi|normale||kabinet|ufficio||prekrasnyi|bella||vysshii|la corte di||krichat|urlare||prejde|prima||magazin|negozio||prostranstvo|lo spazio||vyhod|uscita||ostanovitsia|alloggiare||udar|colpo||baza|base||znanie|la conoscenza||tekst|il testo||siuda|qui||temnyi|dark||zascita|protezione||predlagat|offrire||rukovodstvo|guida||vovse|non||ploscad|piazza||soznanie|la coscienza||grajdanskii|civile||ubit|uccidere||vozrast|eta||molchat|per tacere||soglasitsia|accettare||uchastnik|il partecipante||uchastok|trama||rano|presto||punkt|articolo||nesmotria|nonostante||silno|forte||stol|cosi||soobscit|informare||liniia|la linea||bejat|correre||jelanie|il desiderio di||papa|il papa||kajetsia|sembra||pet|cantare||doktor|dr.||guba|labbro||izvestno|noto||doma|casa||vyzyvat|chiamare||doch|la figlia di||pokazatsia|sembrare||sreda|mercoledi||predsedatel|il presidente||predstavlenie|presentazione||soldat|soldati||hudojnik|artista||prinesti|portare||volos|capelli||orujie|armi||vygliadet|guardare||sootvetstvie|conformita||nikak|non||veter|il vento||vneshnii|esterno||paren|il ragazzo||slujit|servire||zrenie|la visione||poprosit|chiedere||general|il generale||sostoiat|composto||ogon|il fuoco||otdat|dare||boevoi|battaglia||poniatie|il concetto di||stroitelstvo|costruzione||uho|orecchio||vystupat|agire||grud|petto||nos|il naso||stavit|mettere||zavtra|domani||voznikat|verificarsi||kogda|quando||strah|la paura||usluga|servizio||rabochii|di lavoro||chto-nibud|qualcosa||glubokii|profondo||soderjanie|il contenuto||radost|gioia||bezopasnost|sicurezza||nadeiatsia|sperare||produkt|il prodotto||vidimo|a quanto pare||kompleks|il complesso||biznes|business||podniatsia|salire||vspominat|ricordare||malo|poco||sad|giardino||dolgii|lunga||odnovremenno|contemporaneamente||nazyvatsia|chiamato||sotrudnik|dipendente||leto|estate||tiho|tranquillo||zato|ma||priamoi|diretto||kurs|corso||pomogat|aiutare||predlojenie|offerta||finansovyi|finanziaria||otkrytyi|piscina||pochemu-to|per qualche motivo||znachit|significare||vozniknut|verificarsi||rot|bocca||gde-to|da qualche parte||tehnologiia|la tecnologia||znakomyi|familiare||nedavno|di recente||reforma|la riforma||otsutstvie|la mancanza di||nyneshnii|attuale||sobaka|il cane||kamen|pietra||buduscee|il futuro||zvat|a chiamare||rasskaz|la storia||kontrol|controllo||pozvonit|chiamare||reka|il fiume||hvatat|perdere||produkciia|prodotti||summa|importo||tehnika|ingegneria||istoricheskii|storico||vnov|di nuovo||narodnyi|popolare||priamo|proprio||ibo|perche||vypit|bere||zdanie|edificio||sfera|la sfera||znamenityi|il famoso||inache|altrimenti||poteriat|perdere||neobhodimost|la necessita di||bolshii|di piu||fond|il fondo||imetsia|avere||vpered|avanti||podgotovka|preparazione||vchera|ieri||list|foglio||pustoi|vuoto||ocherednoi|ancora una||respublika|la repubblica||hoziaistvo|agricoltura||polnostiu|completamente||poluchatsia|tanto||uchitsia|imparare||ploho|male||volia|la volonta di||sudebnyi|il contenzioso||biudjet|bilancio||vozvrascatsia|tornare||rasti|crescere||sneg|la neve||derevnia|il villaggio||obnarujit|scoprire||mujik|il contadino||postoianno|costantemente||zelenyi|verde||element|elemento||obstoiatelstvo|circostanza||pochuvstvovat|sentire||nemec|tedesco||mnogoe|altro||pobeda|la vittoria||istochnik|fonte||nemeckii|tedesco||zolotoi|d'oro||peredat|invia||tehnicheskii|tecnico||normalnyi|normale||edva|appena||jelat|desiderare||ojidat|aspettare||nekii|un||zvezda|stella||gorodskoi|comunale||vybor|la scelta||sootvetstvuiuscii|corrispondente||massa|massa||sostavit|comporre||itog|totale||sestra|la sorella||chto|che||shest|sei||iasno|chiaro||praktika|pratica||sto|un centinaio di||nesti|portare||opredelit|determinare||provedenie|impresa di||karman|tasca||liubimyi|preferito||rodnoi|nativo||zapadnyi|ovest||obiazatelno|necessariamente||slava|gloria||kuhnia|cucina||opredelenie|definizione||polzovatsia|godere di||bystryi|veloce";
const PROGMEM char morseCodes[] = "a|.-||b|-...||c|-.-.||d|-..||e|.||f|..-.||g|--.||h|....||i|..||j|.---||k|-.-||l|.-..||m|--||n|-.||o|---||p|.--.||q|--.-||r|.-.||s|...||t|-||u|..-||v|...-||w|.--||x|-..-||y|-.--||z|--..||1|.----||2|..---||3|...--||4|....-||5|.....||6|-....||7|--...||8|---..||9|----.||0|-----||.|.-.-.-||,|--..--||?|..--..||'|.----.||!|-.-.--||/|-..-.||(|-.--.||)|-.--.-||&|.-...||:|---...||;|-.-.-.||=|-...-||+|.-.-.||-|-....-||_|..--.-||\"|.-..-.||$|...-..-||@|.--.-.||à|.--.-||ä|.-.-||å|.--.-||ą|.-.-||æ|.-.-||ć|-.-..||ĉ|-.-..||ç|-.-..||ch|----||đ|..-..||ð|..--.||é|..-..||è|.-..-||ę|..-..||ĝ|--.-.||ĥ|----||ĵ|.---.||ł|.-..-||ń|--.--||ñ|--.--||ó|---.||ö|---.||ø|---.||ś|...-...||ŝ|...-.||š|----||þ|.--..||ü|..--||ŭ|..--||ź|--..-.||ż|--..-";

bool existInVocabulary(String query, const PROGMEM char vocabulary[], bool byKey = true) {
  bool isKey = true;
  char tmpChar;
  int len = strlen_P(vocabulary);
  int matches = 0;

  query.trim();

  if (!query.length()) { 
    return false;
  }

  for (int k = 0; k < len; k++) {
    tmpChar = pgm_read_byte_near(vocabulary + k); // read back char from PROGMEM

    if (tmpChar == query[matches]) {
      matches++;

      if (query.length() == matches) {
        if (1 < k || byKey) {
          tmpChar = pgm_read_byte_near(vocabulary + k - query.length());

          if ('|' != tmpChar || (byKey && '|' != (char)pgm_read_byte_near(vocabulary + k - query.length() - 1))) {
            matches = 0;

            continue;
          }
        }

        return true;
      }
    }
    else {
      matches = 0;
    }
  }

  return false;
}

String findInVocabulary(String query, const PROGMEM char vocabulary[], bool byKey = true) {
  String key;
  String value;
  String result;
  char tmpChar;
  int len = strlen_P(vocabulary);
  bool isKey = true;
  bool isWaitForNext = false;

  // Serial.println("in query " + query + " " + String(byKey));

  for (int k = 0; k < len; k++) {
    tmpChar = pgm_read_byte_near(vocabulary + k); // read back char from PROGMEM
    // Serial.print(String(tmpChar));

    if ('|' == tmpChar) {
      k++;

      if (k == len) {
        break;
      }

      tmpChar = pgm_read_byte_near(vocabulary + k);
      // Serial.print(String(tmpChar));

      if ('|' == tmpChar) {
        if (query == (byKey ? key : value)) {
          break;
        }

        isKey = true;
        isWaitForNext = false;
        key = "";
        value = "";

        continue;
      }
      else {
        isKey = false;
      }
    }

    if (isWaitForNext) {
      continue;
    }

    isKey ? key += tmpChar : value += tmpChar;

    if (query.indexOf(byKey ? key : value)) {
      isWaitForNext = true;
      // Serial.print(byKey ? "@" : "#");
      key = "";
      value = "";
    }
  }

  if (query == (byKey ? key : value)) {
    result = byKey ? value : key;
  }

  // Serial.println("in vocabulary !!! " + result);  
  
  return result;
}

String fixSymbols(String message) {
  message.trim();
  message.replace("'", "");
  message.replace("ì", "i");
  message.replace("ò", "o");
  message.replace("ù", "u");
  message.replace("è", "e");
  message.replace("é", "e");
  message.replace("à", "a");

  return message;
}

String morse(String message) {
  message = fixSymbols(message);

  bool isMorse = (!message.indexOf(".") || !message.indexOf("-")) ? true : false;
  String result = "";
  String symbol;
  String nextPart;

  for (int charIndex = 0; charIndex < message.length(); charIndex++) {
    symbol = message.substring(charIndex, charIndex + 1);
    nextPart = message.substring(charIndex + 1);

    // Serial.println("symbol=" + symbol + "||nextPart=" + nextPart);

    if (isMorse) {
      if (!symbol.indexOf(" ")) {
        if (!nextPart.indexOf("  ") && (result.lastIndexOf(" ") != (result.length() - 1))) {
          result += " ";
        }
        
        continue;
      }
      else {
        symbol = symbol + nextPart.substring(0, nextPart.indexOf(" "));
        charIndex += symbol.length() - 1;
      }
    }
    else {
      if (!symbol.indexOf(" ")) {
        if (result.lastIndexOf("  ") != (result.length() - 2)) {
          result += "  ";
        }
        
        continue;
      }
    }

    symbol = findInVocabulary(symbol, morseCodes, !isMorse);

    if (!symbol.length()) {
      symbol = "?";
      // symbol = isMorse ? morse("?") : "?";
    }

    result += isMorse ? symbol : symbol + " ";
  }

  result = fixSymbols(result);

  // Serial.println("search " + message + " || found " + result);
  
  return result;
}

bool addSpace(char space[]) {
  query.trim();

  if (query.length() && !existInVocabulary(morse(query), vocabulary, true)) {
    // query = query.substring(0, (-1 != query.lastIndexOf(" ")) ? query.lastIndexOf(" ") : 0);
    // query.trim();
    // query += " ";
    query = "";
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, (" " == space) ? 1000 : 1250, 150);
    delay(150);
    noTone(speakerPin);
    digitalWrite(ledPin, LOW);
    delay(3000);
    // digitalWrite(ledPin, HIGH);
    // tone(speakerPin, (" " == space) ? 1000 : 1250, 100);
    // delay(100);
    // noTone(speakerPin);
    // digitalWrite(ledPin, LOW);
    // buttonUptime = millis();

    return false;
  }
  else {
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, (" " == space) ? 1000 : 1250, 10);
    timeSignal = timeCurrent + 10;
    query += space;
  }

  return true;
}

bool runCommand(String cmd){
  if (String(".") == cmd) {
    found = lastFound;

    return true;
  }

  return false;
}

void buttonDown() {
    buttonDowntime = millis();
    buttonUptime = 0;
    found = "";
    timeSignal = buttonDowntime + durationDash;
    tone(speakerPin, soundFrequency, durationDash);
    digitalWrite(ledPin, HIGH);
    Serial.println("down");
}

void buttonUp() {
    buttonUptime = millis();
    query += (durationDotDashMean <= (buttonUptime - buttonDowntime)) ? "-" : ".";
    buttonDowntime = 0;
    timeSignal = 0;
    noTone(speakerPin);
    digitalWrite(ledPin, LOW);
    Serial.println("up || " + morse(query) + " | " + query);
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("welcome to \"morse micro language translator\"");
  // Serial.println(findInVocabulary("i", vocabulary));
  // Serial.println(morse("....") + morse(morse("i")));
}

void loop() {
  timeCurrent = millis();

  if (!timeToPlayNextFoundCode && !timeSignal) {
    delay(50); // Z-z-z-z
  }
  else {
    // http://robocraft.ru/blog/arduino/63.html

    if (0 <= (timeCurrent - timeSignal)) {
      noTone(speakerPin);
      digitalWrite(ledPin, LOW);
      timeSignal = 0;
    }

    // soundTone = 1 / (2 * soundFrequency);
    // if (timeSignal && !(timeCurrent % 4)) {
    //   digitalWrite(speakerPin, HIGH);
    //   delay(2);
    //   digitalWrite(speakerPin, LOW);
    //   delay(2);
    // }
  }

  isPressedButton = !digitalRead(buttonPin);
  timeCurrent = millis();

  if (isPressedButton && !buttonDowntime) {
    buttonDown();
  }
  else if (!isPressedButton && buttonDowntime) {
    buttonUp();
  }
  else if (buttonUptime && !query.endsWith(" ") && (durationLetterSpace <= (timeCurrent - buttonUptime))) {
    addSpace(" ");
  }
  else if (buttonUptime && !query.endsWith("   ") && query.endsWith(" ") && (durationWordSpace <= (timeCurrent - buttonUptime))) {
    addSpace("   ");
  }
  else if (buttonUptime && (durationStopOnTime <= (timeCurrent - buttonUptime))) {
    query.trim();

    if (!runCommand(query)) {
      found = morse(query);
      found = findInVocabulary(found, vocabulary, true);
      found = morse(found);
    }

    query = "";
    buttonUptime = 0;

    if (found.length()) {
      lastFound = found;
      found = "   " + found;
      timeSignal = timeCurrent + 10;
      tone(speakerPin, 1500, 10);
      digitalWrite(ledPin, HIGH);
      Serial.println("found in vocabulary " + found);
    }
    else {
      timeSignal = timeCurrent + 150; 
      tone(speakerPin, 1500, 150);
      digitalWrite(ledPin, HIGH);
      Serial.println("nothing found");
    }

    found.replace("?", morse("?"));
  }
  else if (found.length() && (0 <= (timeCurrent - timeToPlayNextFoundCode))) {
    if (!found.indexOf(".")) {
      tone(speakerPin, soundFrequency, durationDot / soundSpeed);
      digitalWrite(ledPin, HIGH);
      timeSignal = timeCurrent + durationDot / soundSpeed;
      timeToPlayNextFoundCode = timeSignal + durationIntraCharacterGap / soundSpeed;
    }
    else if (!found.indexOf("-")) {
      tone(speakerPin, soundFrequency, durationDash / soundSpeed);
      digitalWrite(ledPin, HIGH);
      timeSignal = timeCurrent + durationDash / soundSpeed;
      timeToPlayNextFoundCode = timeSignal + durationIntraCharacterGap / soundSpeed;
    }
    else if (!found.indexOf("   ")) {
      timeToPlayNextFoundCode = timeCurrent + durationWordSpace / soundSpeed;
      found = found.substring(2);
    }
    else if (!found.indexOf(" ")) {
      timeToPlayNextFoundCode = timeCurrent + durationLetterSpace / soundSpeed;
    }

    found = found.substring(1);
  }
  else if (timeToPlayNextFoundCode && (0 <= (timeCurrent - timeToPlayNextFoundCode))) {
    timeToPlayNextFoundCode = 0;
  }
}
