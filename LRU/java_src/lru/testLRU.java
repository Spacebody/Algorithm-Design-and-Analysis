
package lru;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;
/**
 * test LRU
 */
public class testLRU 
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        System.out.println("Please enter capacity:");
        int capacity = input.nextInt();
        LRU<Integer, Integer> map = new LRU<Integer, Integer>(capacity);
        System.out.println("Enter integers, end for entering 'q': ");
        
        //input
        map.put(1,1); 
        map.put(3,3);
        map.put(2,2);
        map.put(1,1);
        map.put(5,5);
        map.put(4,4);
        map.put(3,3);
       
        //visit the data
        map.get(1); 
        map.get(3);
        map.get(2);
        map.get(1);
        map.get(5);
        map.get(4);
        map.get(3);
        System.out.println("The data in cache are: ");
        for(Iterator<Map.Entry<Integer,Integer>> it=map.entrySet().iterator();it.hasNext();)
        {
            System.out.println(it.next().getKey());
        }
        System.out.println();
        //put again
        map.put(7,7);
        map.put(6,6);
        map.put(8,8);
        System.out.println("The data in cache are: ");
        for(Iterator<Map.Entry<Integer,Integer>> it=map.entrySet().iterator();it.hasNext();)
        {
            System.out.println(it.next().getKey());
        }
        System.out.println();
        
        map.put(9,9);
        System.out.println("The data in cache are: ");
        for(Iterator<Map.Entry<Integer,Integer>> it=map.entrySet().iterator();it.hasNext();)
        {
            System.out.println(it.next().getKey());
        }
    }
}
