package demo.com.hashmap;

/**
 * 手写HashMap 关键代码
 * Created by 花歹 on 2018/9/11.
 * Email:   gatsbywang@126.com
 * Description:
 * Thought:
 */

public class HashMap<K, V> {

    /**
     * 散列table (桶)
     */
    public MapEntry[] table;

    /**
     * d当前存放的个数
     */
    transient int size;

    /**
     * 扩容阈值
     */
    int threshold = 8;

    /**
     * 扩容因子，平衡查找的性能
     */
    final float loadFactor = 0.75f;

    public class MapEntry<K, V> {
        K key;
        V value;
        MapEntry<K, V> next;
        int hash; //key 的 hash

        public MapEntry(int hash, K key, V value, MapEntry<K, V> next) {
            this.key = key;
            this.value = value;
            this.next = next;
            this.hash = hash;
        }
    }

    public V put(K key, V value) { //如果有数组 则是O(n)级别
        //1、构建一个MapEntry
        //2、for 循环数组有没有包含该key ,如果有替换（循环数组）
        //3、 没有就新增

        if (table == null) {
            table = new MapEntry[8];
        }

        if (key == null) {

            //HashMap 里是放在index 0位置
            return null;
        }

        int hash = hash(key);
        int index = getIndex(hash, table.length);

        //判断有没有存在key
        //1、hash 相等 两个对象不一定相等
        //2、两个对象不相等，那么hash一定不相等
        for (MapEntry<K, V> e = table[index]; e != null; e = e.next) {
            Object k;//一丁点优化
            if (e.hash == hash && ((k = e.key) == key || key.equals(k))) {
                V oldValue = e.value;
                e.value = value;
                return oldValue;
            }

        }

        //3、添加一个新的MapEntry
        addEntry(hash, key, value, index);

        return null;

//        table[size++] = new MapEntry(key, value);
    }

    /**
     * 添加一个新的Entry
     *
     * @param hash
     * @param key
     * @param value
     * @param index
     */
    private void addEntry(int hash, K key, V value, int index) {
        //
        // 判断要不要扩容 mask_bits(value()>>hash_shift,hash_mask)
        //hash_shift = 16 value()对象的地址，jdk源码中的jni中 hashcode 的源码就是右移16位
        //1、hash 相等 两个对象不一定相等
        //2、hash值不相等的，两个对象肯定不相等
        //上面

        if (size >= threshold && table[index] != null) {
            resize(size << 1);
            //重新计算index
            index = getIndex(hash, table.length);

        }

        createEntry(hash, key, value, index);

        size++;
    }

    /**
     * 创建一个新的
     *
     * @param hash
     * @param key
     * @param value
     * @param index
     */
    private void createEntry(int hash, K key, V value, int index) {
        MapEntry<K, V> newEntry = new MapEntry<>(hash, key, value, table[index]);
        table[index] = newEntry; //放index桶最前面
        size++;
    }

    private void resize(int newCapacity) {
        MapEntry<K, V>[] newTable = new MapEntry[newCapacity];
        transfrom(newTable);

        //
        table = newTable;
        threshold = (int) (newCapacity * loadFactor);
    }

    /**
     * 重新计算挪动 散列
     *
     * @param newTable
     */
    private void transfrom(MapEntry<K, V>[] newTable) {
        int newCapacity = newTable.length;

        for (MapEntry<K, V> e : table) {
            while (null != e) {
                //从原来的数组中获取数据Entry,保证新的数组能够链起来
                MapEntry<K, V> next = e.next;
                int index = getIndex(e.hash, newCapacity);

                //保证旧链表能够链到新的链表中。
                e.next = newTable[index];
                newTable[index] = e;
                e = next;
            }
        }
    }

    /**
     * 通过hash 值找打所在的table的index
     *
     * @param hash
     * @return
     */
    private int getIndex(int hash, int length) {
        return hash & length - 1;
    }

    private int hash(K key) {
        int h = 0;
        return (key == null) ? 0 : (h = key.hashCode() ^ (h >>> 16));
    }

    public V get(K key) { //如果通过循环数组，那还是O（n）级别
        if (key == null) {
            //自行看源码
            return null;
        }

        MapEntry<K, V> entry = getEntry(key);
        return entry == null ? null : entry.value;
    }

    private MapEntry<K, V> getEntry(K key) {
        int hash = hash(key);
        int index = getIndex(hash, table.length);

        //判断有没有存在该key
        for (MapEntry<K, V> e = table[index]; e != null; e = e.next) {
            Object k;//一丁点优化
            if (e.hash == hash && ((k = e.key) == key || key.equals(k))) {
                return e;
            }
        }
        return null;
    }

    public int getSize(){
        return table.length;
    }
}
