#ifndef DEF_BUZZER
#define DEF_BUZZER

class Buzzer
{
    private:
    int pinBuzzer;
    public:
    /**
     * @brief      Constructeur par défaut de la classe Buzzer.
    */
    Buzzer();
   // ~Buzzer();
    /**
     * @brief      Initialisation du buzzer, appellé par le constructeur
    */
    virtual void init();
    /**
     * @brief      Récupération du pin du buzzer.
     * @return     Le pin du buzzer.
    */
    virtual int Get_pin();
    /**
     * @brief      Fait sonner le buzzer.
    */
    void BuzzOn();
    void BuzzOff();
};
#endif
