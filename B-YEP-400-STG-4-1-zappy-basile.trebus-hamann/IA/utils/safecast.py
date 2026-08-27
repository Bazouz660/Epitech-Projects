import logging

def cast_value(val, to_type: type):
    try:
        return to_type(val)
    except:
        logging.critical("Safe cast failed")