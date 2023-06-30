
int CPersonalAgenda::bin_search_byName(const string &name, const string &surname) const{
    int left = 0, right = int(dataBase_byName.size() - 1);
    int mid;

    while (left <= right){
        mid = (left + right) / 2;
        int sValue = ::strcmp(dataBase_byName[mid].surname.c_str(), surname.c_str());
        if (sValue == 0) {
            int nValue = ::strcmp(dataBase_byName[mid].name.c_str(), name.c_str());
            if (nValue == 0){
                return mid;
            }
            else if (nValue > 0){
                while (sValue == 0 && mid > left){
                    mid -= 1;
                    sValue = ::strcmp(dataBase_byName[mid].surname.c_str(), surname.c_str());
                    nValue = ::strcmp(dataBase_byName[mid].name.c_str(), name.c_str());

                    if (sValue == 0 && nValue == 0){
                        return mid;
                    }
                }
                if (mid == left){
                    return -1;
                }
            }
            else{
                while (sValue == 0 && mid < right){
                    mid += 1;
                    sValue = ::strcmp(dataBase_byName[mid].surname.c_str(), surname.c_str());
                    nValue = ::strcmp(dataBase_byName[mid].name.c_str(), name.c_str());

                    if (sValue == 0 && nValue == 0){
                        return mid;
                    }
                }
                if (mid == right){
                    return -1;
                }
            }
        }
        else if (sValue > 0){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }

    return -1;
}
int CPersonalAgenda::bin_search_byEmail(const string& email) const{
    int left = 0, right = int(dataBase_byEmail.size() - 1);
    int mid;

    while (left <= right){
        mid = (left + right) / 2;
        int value = ::strcmp(dataBase_byEmail[mid].email.c_str(), email.c_str());
        if (value == 0) {
            return mid;
        }
        else if (value > 0){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }

    return -1;
}
