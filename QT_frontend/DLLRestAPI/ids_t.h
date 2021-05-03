#ifndef IDS_T_H
#define IDS_T_H

// Struct to package ids for easier transportasion over functions
struct ids_t {
    // Fields
    int customer_id;
    int account_id;
    int card_id;

    // Methods
    ids_t() {}
    ids_t(int init) {
        customer_id = init;
        account_id = init;
        card_id = init;
    }
    ids_t(int customer_id, int account_id, int card_id) {
        this->customer_id = customer_id;
        this->account_id = account_id;
        this->card_id = card_id;
    }

    void operator=(int init) {
        customer_id = init;
        account_id = init;
        card_id = init;
    }
};

#endif  // IDS_T_H
