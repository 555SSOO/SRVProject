package util;

import java.util.List;

public class ArrayUtil {


    public static int getIndex(Integer number, List array)
    {
        for (int i = 0; i < array.size(); i++)
        {
            Integer item = (Integer) array.get(i);
            if (item.equals(number))
            {
                return i;
            }
        }

        return -1;
    }

}
