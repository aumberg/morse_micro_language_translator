int buttonPin = 2;
int speakerPin = 3;
int ledPin = 4;

int soundSpeed = 1;
int soundFrequency = 100;
// https://en.wikipedia.org/wiki/Morse_code#Representation.2C_timing_and_speeds
int durationDot = 100;
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

// !!!!!!!!!!! trouble with long string - https://github.com/arduino/Arduino/issues/1401
// i compile code with http://uecide.org/

const PROGMEM char morseCodes[] = "a|.-||b|-...||c|-.-.||d|-..||e|.||f|..-.||g|--.||h|....||i|..||j|.---||k|-.-||l|.-..||m|--||n|-.||o|---||p|.--.||q|--.-||r|.-.||s|...||t|-||u|..-||v|...-||w|.--||x|-..-||y|-.--||z|--..||1|.----||2|..---||3|...--||4|....-||5|.....||6|-....||7|--...||8|---..||9|----.||0|-----||.|.-.-.-||,|--..--||?|..--..||'|.----.||!|-.-.--||/|-..-.||(|-.--.||)|-.--.-||&|.-...||:|---...||;|-.-.-.||=|-...-||+|.-.-.||-|-....-||_|..--.-||\"|.-..-.||$|...-..-||@|.--.-.||à|.--.-||ä|.-.-||å|.--.-||ą|.-.-||æ|.-.-||ć|-.-..||ĉ|-.-..||ç|-.-..||ch|----||đ|..-..||ð|..--.||é|..-..||è|.-..-||ę|..-..||ĝ|--.-.||ĥ|----||ĵ|.---.||ł|.-..-||ń|--.--||ñ|--.--||ó|---.||ö|---.||ø|---.||ś|...-...||ŝ|...-.||š|----||þ|.--..||ü|..--||ŭ|..--||ź|--..-.||ż|--..-";
// https://en.wiktionary.org/wiki/Wiktionary:Frequency_lists
// russian translit to italiano
const PROGMEM char vocabulary[] = "i|e||v|in||ne|non||na|su||ja|io||byt|essere||on|esso||s|da||chto|cosa||a|e||po|da||jeto|questo||ona|esso||jetot|questo||k|a||no|ma||oni|essi||my|noi||kak|come||iz|da||u|a||kotoryj|quale||to|poi||za|per||svoj|la sua||chto|cosa||ves|tutto||god|anno||ot|da||tak|cosi||o|di||dlja|a||ty|voi||zhe|il||vse|tutto||tot|il||moch|essere in grado di||vy|voi||chelovek|uomo||takoj|come||ego|la sua||skazat|dire||tolko|solo||ili|o||eshhjo|di piu||by|voluto||sebja|se stesso||odin|uno||kak|come||uzhe|gia||do|prima||vremja|tempo||esli|se||sam|se stesso||kogda|dove||drugoj|altro||vot|qui||govorit|parlare||nash|nostro||moj|mio||znat|sapere||stat|diventare||pri|a||chtoby|che||delo|affari||zhizn|vita||kto|chi||pervyj|primo||ochen|molto||dva|due||den|giorno||ejo|lei||novyj|nuovo||ruka|mano||dazhe|anche||vo|in||so|da||raz|tempo||gde|dove||tam|la||pod|sotto||mozhno|puo||nu|bene||kakoj|quale||posle|dopo||ih|loro||rabota|lavoro||bez|senza||samyj|piu||potom|poi||nado|deve||hotet|scegliere||li|se||slovo|parola||idti|andare||bolshoj|grande||dolzhen|dovrebbe||mesto|luogo||imet|avere||nichto|niente||to|poi||sejchas|ora||tut|qui||lico|faccia||kazhdyj|tutti||drug|amico||net|no||teper|adesso||ni|o||glaz|occhio||tozhe|anche||togda|poi||videt|vedere||vopros|problema||cherez|attraverso||da|si||zdes|qui||dom|casa||da|si||potomu|perché||storona|partito||kakoj-to|alcuni||dumat|pensare||sdelat|fare||strana|nazione||zhit|vivere||chem|di||mir|mondo||ob|di||poslednij|ultimo||sluchaj|caso||golova|testa||bolee|di piu||delat|fare||chto-to|qualcosa||smotret|orologio||rebenok|bambino||prosto|solo||konechno|naturalmente||sila|energia||rossijskij|russo||konec|fine||pered|prima||neskolko|alcuni||vid|vista||sistema|sistema||vsegda|sempre||rabotat|lavoro||mezhdu|tra||tri|tre||net|no||ponjat|capire||pojti|andare||chast|parte||sprosit|chiedere||gorod|citta||dat|dare||takzhe|anche||nikto|nessuno||ponimat|capire||poluchit|ricevere||otnoshenie|relazione||lish|solo||vtoroj|il secondo||imenno|esattamente||vash|il tuo||hotja|anche se||ni|o||sidet|sedersi||nad|sopra||zhenshhina|donna||okazatsja|essere||russkij|russo||odin|uno||vzjat|prendere||prijti|venire||javljatsja|apparire||dengi|soldi||pochemu|perché||vdrug|improvvisamente||ljubit|amare||stoit|costo||pochti|quasi||zemlja|terra||obshhij|generale||ved|dopotutto||mashina|auto||odnako|tuttavia||srazu|subito||horosho|ok||voda|acqua||otec|padre||vysokij|alto||ostatsja|soggiorno||vyjti|uscita||mnogo|lotto||problema|problema||nachat|inizio||horoshij|bene||chas|h||jeto|questo||segodnja|oggi||pravo|destra||sovsem|tutto||noga|gamba||schitat|contare||glavnyj|capo||reshenie|decisione||uvidet|vedere||dver|porta||kazatsja|apparire||obraz|immagine||pisat|scrivere||istorija|storia||luchshij|migliore||vlast|energia||zakon|legge||vse|tutto||vojna|guerra||bog|dio||golos|voce||najti|trovare||pojetomu|cosi||stojat|stare in piedi||voobshhe|affatto||tysjacha|mille||bolshe|meglio||vmeste|insieme||malenkij|piccolo||kniga|libro||nekotoryj|alcuni||reshit|risolvere||ljuboj|qualsiasi||vozmozhnost|opportunita||rezultat|risultato||noch|notte||stol|tavola||nikogda|mai||imja|nome||oblast|area||molodoj|giovane||projti|andare||naprimer|ad esempio,||statja|articolo||ono|esso||chislo|numero||kompanija|azienda||pro|di||gosudarstvennyj|stato||polnyj|completo||prinjat|adottare||narod|persone||nikakoj|no||sovetskij|sovietico||zhena|moglie||nastojashhij|vero||vsjakij|ogni||gruppa|gruppo||razvitie|sviluppo||process|processo||sud|corte||davat|dare||otvetit|risposta||staryj|vecchio||uslovie|stato||tvoj|il tuo||poka|mentre||sredstvo|mezzi||pomnit|ricorda||nachalo|inizio||zhdat|aspettare||svet|luce||pora|è tempo di||put|strada||dusha|anima||kuda|dove||nuzhno|bisogno||raznyj|diverso||nuzhnyj|necessario||uroven|livello||inoj|altro||forma|forma||svjaz|collegamento||uzh|davvero||minuta|minuto||krome|inoltre||nahoditsja|essere||opjat|di nuovo||mnogij|lotto||belyj|bianco||sobstvennyj|proprio||ulica|strada||chernyj|nero||napisat|scrivere||vecher|sera||snova|di nuovo||osnovnoj|primario||kachestvo|qualita||mysl|pensiero||doroga|strada||mat|madre||dejstvie|azione||mesjac|mese||ostavatsja|soggiorno||gosudarstvo|stato||jazyk|lingua||ljubov|amare||vzgljad|vista||mama|mamma||igrat|giocare||dalekij|lontano||lezhat|bugia||nelzja|non devi||vek|secolo||shkola|scuola||podumat|pensiero||ujti|fuga||cel|bersaglio||sredi|tra||obshhestvo|societa||posmotret|vedere||dejatelnost|attivita||organizacija|organizzazione||kto-to|qualcuno||vernutsja|ritorno||prezident|presidente||komnata|stanza||porjadok|ordine||moment|tempo||teatr|teatro||sledovat|seguire||chitat|leggere||pismo|lettera||podobnyj|simile||sledujushhij|il prossimo||utro|mattina||osobenno|particolarmente||pomoshh|aiuto||situacija|situazione||rol|ruolo||byvat|visita||hodit|camminare||rubl|rublo||nachinat|inizio||pojavitsja|apparire||smysl|significato||sostojanie|stato||nazyvat|chiamata||rjadom|nelle vicinanze||kvartira|appartamento||nazad|fa||ravnyj|uguale||iz-za|a causa di||organ|organo||vnimanie|attenzione||telo|corpo||trud|lavoro||prijtis|venire||hotetsja|volere||syn|figlio||mera|misurare||pjat|cinque||smert|morte||zhivoj|vivente||rynok|mercato||programma|programma||zadacha|compito||predprijatie|azienda||izvestnyj|conosciuto||okno|finestra||vesti|piombo||sovershenno|completamente||voennyj|militare||razgovor|conversazione||pokazat|spettacolo||pravitelstvo|governo||vazhnyj|importante||semja|famiglia||velikij|ottimo||proizvodstvo|produzione||prostoj|semplice||znachit|cosi||tretij|terzo||skolko|come||ogromnyj|ottimo||davno|lungo||politicheskij|politico||informacija|informazioni||dejstvitelno|davvero||polozhenie|posizione||postavit|mettere||bojatsja|paura||nakonec|infine||centr|centro||proishodit|prendere posto||otvet|risposta||muzh|marito||avtor|autore||vse-taki|ancora||stena|muro||sushhestvovat|esistere||dazhe|anche||interes|interesse||stanovitsja|diventare||federacija|federazione||pravilo|regola||oba|entrambi||chasto|spesso||moskovskij|mosca||upravlenie|gestione||slyshat|sentire||bystro|veloce||smoch|essere in grado di||zametit|osservare||kak-to|in qualche modo||muzhchina|uomo||dolgo|lungo||pravda|verita||ideja|idea||partija|partito||inogda|a volte||ispolzovat|uso||pytatsja|provare||gotovyj|pronto||chut|leggermente||zachem|per che cosa||predstavit|immaginare||chuvstvovat|sentire||sozdat|creare||sovet|consigli||schet|punto||serdce|cuore||dvizhenie|mozione||veshh|cosa||material|materiale||nedelja|settimana||chuvstvo|sentimento||zatem|poi||dannyj|il||zanimatsja|fare||prodolzhat|continuare||krasnyj|rosso||glava|testa||ko|a||slushat|ascolta||nauka|scienza||uznat|scoprire||rjad|serie||gazeta|giornale||prichina|motivo||protiv|contro||plecho|spalla||sovremennyj|moderno||cena|prezzo||plan|piano||priehat|venire||rech|discorso||chetyre|quattro||otvechat|risposta||tochka|punto||osnova|fondazione||tovarishh|compagno||kultura|cultura||slishkom|anche||rasskazyvat|raccontare||vpolne|bella||dalee|ulteriore||rasskazat|raccontare||dannye|dati||predstavljat|presentare||mnenie|vista||socialnyj|sociale||okolo|di||dokument|documento||institut|istituto||hod|mossa||brat|prendere||zabyt|dimenticare||proekt|progetto||rannij|presto||vstrecha|incontro||osobyj|speciale||celyj|tutto||direktor|direttore||provesti|condotta||spat|sonno||plohoj|male||mozhet|puo||vprochem|tuttavia||silnyj|forte||navernoe|probabilmente||skoryj|presto||ved|dopotutto||srok|tempo||palec|dito||opyt|esperienza||pomoch|aiuto||bolshe|meglio||prihodit|venire||sluzhba|servizio||krupnyj|ottimo||vnutrennij|casa||prosit|chiedere||vspomnit|ricorda||otkryt|aperto||privesti|piombo||sudba|destino||poka|mentre||devushka|ragazza||poskolku|da||ochered|turno||les|foresta||pust|lasciare||jekonomicheskij|economico||ostavit|conservare||pravyj|destra||sostav|struttura||slovno|come||federalnyj|federale||sprashivat|chiedere||prinimat|prendere||chlen|membro||iskat|ricerca||blizkij|chiudere||kolichestvo|quantita||pohozhij|simile||sobytie|evento||obekt|facilita||zal|sala||sozdanie|creazione||vojti|entrare||razlichnyj|diverso||znachenie|valore||nazvat|chiamata||dostatochno|basta||period|periodo||hot|anche se||shag|mossa||neobhodimyj|richiesto||uspet|fermo||proizojti|succedere||brat|fratello||iskusstvo|arte||edinstvennyj|solo||legkij|luce||struktura|struttura||vyhodit|ritirare||nomer|numero||predlozhit|offerta||primer|esempio||pit|bere||issledovanie|ricerca||grazhdanin|cittadino||gljadet|guarda||chelovecheskij|umano||igra|gioco||nachalnik|capo||sej|questo||rost|crescita||ehat|andare||mezhdunarodnyj|internazionale||tema|tema||princip|principio||dorogoj|costoso||popast|ottenere||desjat|dieci||nachatsja|inizio||verit|credere||metod|metodo||tip|tipo||film|film||nebolshoj|piccolo||derzhat|mantenere||libo|o||pozvoljat|consentire||kraj|bordo||mestnyj|locale||menee|di meno||gost|ospite||kupit|acquistare||uhodit|partire||sobiratsja|raccogliere||vozduh|aria||tuda|la||otnositsja|raccontare||byvshij|ex||trebovat|richiedere||harakter|carattere||borba|combattimento||ispolzovanie|uso||kstati|a proposito||podojti|aumentare||razmer|taglia||udatsja|allenamento||obrazovanie|educazione||poluchat|ricevere||malchik|ragazzo||krov|sangue||rajon|area||nebo|paradiso||amerikanskij|americana||armija|esercito||klass|classe||predstavitel|rappresentante||uchastie|parte||devochka|ragazza||politika|politica||snachala|primo||geroj|eroe||kartina|immagine||shirokij|largo||dollar|dollaro||spina|indietro||territorija|territorio||mirovoj|mondo||pol|pavimentazione||tjazhelyj|pesante||dovolno|bella||pole|campo||zh|bene||izmenenie|cambiamento||umeret|morire||bolee|di piu||napravlenie|direzione||risunok|immagine||techenie|flusso||vozmozhnyj|possibile||cerkov|chiesa||bank|banca||otdelnyj|singolo||srednij|media||krasivyj|bellissimo||scena|scena||naselenie|popolazione||bolshinstvo|piu||sest|sedersi||dvadcat|venti||sluchitsja|succedere||muzyka|musica||korotkij|breve||pravda|verita||prohodit|passare||sostavljat|essere||svoboda|liberta||pamjat|memoria||prihoditsja|cadere||prichem|e||komanda|squadra||ustanovit|stabilire||sojuz|unione||budto|come se||podnjat|raccogliere||vrach|medico||sereznyj|grave||dogovor|accordo||staratsja|provare||umet|essere in grado di||vstat|su||derevo|di legno||interesnyj|interessante||fakt|fatto||dobryj|tipo||vsego|totale||hozjain|maestro||nacionalnyj|nazionale||odnazhdy|un giorno||dlinnyj|lungo||priroda|natura||domoj|casa||strashnyj|spaventevole||proshlyj|ultimo||budto|come se||obshhestvennyj|pubblico||ugol|angolo||chtob|a||telefon|telefono||pozicija|posizione||provodit|condotta||skoro|presto||naibolee|piu||dvor|cortile||obychno|generalmente||brosit|gettare||razve|davvero||pisatel|scrittore||samolet|aereo||obem|volume||daleko|lontano||rod|gara||solnce|sole||vera|vera||bereg|costa||spektakl|prestazione||firma|ditta||sposob|moda||zavod|impianto||cvet|colore||trudno|difficile||zhurnal|rivista||rukovoditel|direttore||specialist|esperto||vozmozhno|forse||detskij|bambini||tochno|esattamente||objasnit|spiegare||ocenka|valutazione||edinyj|singolo||snjat|sparare||opredelennyj|certo||nizkij|basso||nravitsja|come||uslyshat|sentire||region|regione||svjazat|cravatta||pesnja|canzone||procent|per cento||roditel|genitore||pozvolit|lasciare||chuzhoj|straniera||more|mare||strannyj|strano||trebovanie|domanda||chistyj|netto||vesma|molto||kakoj-nibud|alcuni||osnovanie|fondazione||polovina|mezzo||poehat|andare||polozhit|mettere||vhodit|entrare||legko|facile||pozdnij|in ritardo||roman|romanzo||krug|round||analiz|analisi||stihi|poesie||avtomobil|auto||specialnyj|speciale||jekonomika|economia||literatura|letteratura||bumaga|carta||vmesto|invece||vpervye|primo||vidno|si puo vedere||nauchnyj|ricerca||okazyvatsja|risultare||pojet|poeta||pokazyvat|spettacolo||stepen|livello||vyzvat|causa||kasatsja|toccare||gospodin|sig.||nadezhda|sperare||slozhnyj|complicato||vokrug|in giro||predmet|cosa||otmetit|voto||zajavit|richiesta||variant|opzione||ministr|ministro||otkuda|donde||realnyj|vero||granica|confine||dejstvovat|atto||duh|spirito||model|modello||operacija|operazione||para|coppia||son|sognare||nemnogo|piccolo||nazvanie|titolo||um|mente||povod|motivo||starik|vecchio uomo||sposobnyj|capace||malo|alcuni||million|milione||malyj|piccolo||starshij|piu vecchio||uspeh|successo||prakticheski|praticamente||poluchitsja|risultare||lichnyj|personale||schaste|felicita||neobhodimo|necessario||svobodnyj|libero||rebjata|bambini||obychnyj|solito||kabinet|gabinetto||prekrasnyj|bellissimo||vysshij|superiore||krichat|urlo||prezhde|prima||magazin|negozio||prostranstvo|spazio||vyhod|produzione||ostanovitsja|soggiorno||udar|colpo||baza|base||znanie|conoscenza||tekst|testo||sjuda|qui||temnyj|buio||zashhita|protezione||predlagat|offerta||rukovodstvo|comando||vovse|tutto||ploshhad|area||soznanie|coscienza||grazhdanskij|civile||ubit|uccidere||vozrast|eta||molchat|di tacere||soglasitsja|concordare||uchastnik|partecipante||uchastok|area||rano|presto||punkt|punto||nesmotrja|nonostante||silno|fortemente||stol|cosi||soobshhit|rapporto||linija|linea||bezhat|correre||zhelanie|desiderio||papa|papa||kazhetsja|sembra||pet|cantare||doktor|medico||guba|labbro||izvestno|conosciuto||doma|case||vyzyvat|causa||doch|figlia||pokazatsja|apparire||sreda|mercoledi||predsedatel|presidente||predstavlenie|prestazione||soldat|soldato||hudozhnik|artista||prinesti|portare||volos|capelli||oruzhie|armi||vygljadet|guarda||sootvetstvie|conformita||nikak|in nessun modo||veter|vento||vneshnij|all'aperto||paren|tipo||sluzhit|servire||zrenie|vista||poprosit|chiedere||general|gen.||sostojat|consistere||ogon|fuoco||otdat|dare||boevoj|combattente||ponjatie|nozione||stroitelstvo|costruzione||uho|orecchio||vystupat|sporgere||grud|seno||nos|naso||stavit|mettere||zavtra|domani||voznikat|sorgere||kogda|dove||strah|paura||usluga|servizio||rabochij|lavoro||chto-nibud|qualcosa||glubokij|profondita||soderzhanie|contenuto||radost|gioia||bezopasnost|sicurezza||nadejatsja|sperare||produkt|prodotto||vidimo|apparentemente||kompleks|complesso||biznes|affari||podnjatsja|salire||vspominat|ricorda||malo|alcuni||sad|giardino||dolgij|lungo||odnovremenno|contemporaneamente||nazyvatsja|essere chiamato||sotrudnik|dipendente||leto|estate||tiho|dolcemente||zato|ma||prjamoj|dritto||kurs|corso||pomogat|aiuto||predlozhenie|sentenza||finansovyj|finanziario||otkrytyj|aperto||chto-to|in qualche modo||znachit|significare||vozniknut|esperienza||rot|bocca||gde-to|da qualche parte||tehnologija|tecnologia||znakomyj|familiare||nedavno|recentemente||reforma|riforma||otsutstvie|assenza||nyneshnij|presente||sobaka|cane||kamen|stone||budushhee|futuro||zvat|chiamata||rasskaz|storia||kontrol|controllo||pozvonit|chiamata||reka|fiume||hvatat|bastare||produkcija|prodotti||summa|somma||tehnika|attrezzatura||istoricheskij|storico||vnov|di nuovo||narodnyj|popolare||prjamo|dritto||ibo|per||vypit|bere||zdanie|costruzione||sfera|area||znamenityj|famoso||inache|altrimenti||poterjat|perdere||neobhodimost|bisogno||bolshij|di piu||fond|fondo||imetsja|esistere||vpered|avanti||podgotovka|formazione||vchera|ieri||list|foglio||pustoj|vuoto||ocherednoj|il prossimo||respublika|repubblica||hozjajstvo|economia||polnostju|completamente||poluchatsja|ottenuti||uchitsja|studio||ploho|male||volja|volonta||sudebnyj|giudiziario||bjudzhet|bilancio||vozvrashhatsja|ritorno||rasti|crescere||sneg|neve||derevnja|villaggio||obnaruzhit|scoprire||muzhik|muzhik||postojanno|costantemente||zelenyj|verde||jelement|elemento||obstojatelstvo|circostanza||pochuvstvovat|sentire||nemec|tedesco||mnogoe|molto||pobeda|vittoria||istochnik|fonte||nemeckij|tedesco||zolotoj|oro||peredat|presentare||tehnicheskij|tecnico||normalnyj|normale||edva|a mala pena||zhelat|desiderare||ozhidat|aspettare||nekij|alcuni||zvezda|stella||gorodskoj|citta||vybor|selezione||sootvetstvujushhij|appropriato||massa|peso||sostavit|trucco||itog|risultato||sestra|sorella||chto|cosa||shest|sei||jasno|chiaro||praktika|pratica||sto|cento||nesti|trasportare||opredelit|determinare||provedenie|detenzione||karman|tasca||ljubimyj|favorito||rodnoj|casa||zapadnyj|western||objazatelno|necessariamente||slava|fama||kuhnja|cucina||opredelenie|determinazione||polzovatsja|uso||bystryj|veloc||";

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
  message.replace("ì", "i");
  message.replace("ò", "o");
  message.replace("ù", "u");

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

  if (!timeSignal) {
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
