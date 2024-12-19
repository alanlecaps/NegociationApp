
#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol {
private:
    int nbr_tours;
    int nbr_obl_achet;
    int penalité;
    int neg_meme_temps;
    bool differer;

public:
    // Constructor
    Protocol();

    // Getter and Setter declarations
    int getNbrTours() const;
    void setNbrTours(int value);

    int getNbrOblAchet() const;
    void setNbrOblAchet(int value);

    int getPenalite() const;
    void setPenalite(int value);

    int getNegMemeTemps() const;
    void setNegMemeTemps(int value);

    bool isDifferer() const;
    void setDifferer(bool value);
};

#endif // PROTOCOL_H
