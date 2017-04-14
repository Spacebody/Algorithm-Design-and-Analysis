
package lru;
import java.util.Map;
import java.util.LinkedHashMap;
/**
 * @param <K>
 * @param <V>
 * use LinkedHashMap
 */
public class LRU<K, V> extends LinkedHashMap<K, V> 
{
    private static final long serialVersionUID = 1L;
    private final int capacity;

    LRU(int capacity) 
    {
        super(capacity, 0.75f, true);
        this.capacity = capacity; //modified the capacity
    }

    @Override //override the function
    public boolean removeEldestEntry(Map.Entry<K, V> eldest) 
    {
        return size() > capacity; //if larger than capacity, remove it
    }
    
}


