using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemSpawner : MonoBehaviour
{
    public Transform[] spawnPoints;
    public GameObject[] foodPrefabs;
    float timer;
    int waitingTime;

    // Start is called before the first frame update
    void Start()
    {
        timer = 0.0f;
        waitingTime = 1;
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;
        if(timer>waitingTime)
        {
            Spawn();
            timer = 0; 
        }
    }

    void Spawn()
    {
        int randFood = Random.Range(0, foodPrefabs.Length);
        int randSpawn = Random.Range(0, spawnPoints.Length);

        //Instantiate(foodPrefabs[0], spawnPoints[randSpawn].position, transform.rotation);

        Instantiate(foodPrefabs[randFood], spawnPoints[randSpawn].position, transform.rotation);
        
        
    }
}
