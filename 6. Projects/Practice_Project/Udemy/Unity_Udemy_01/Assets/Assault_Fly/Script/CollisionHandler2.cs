using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.SceneManagement;


public class CollisionHandler2 : MonoBehaviour
{
    [SerializeField] float loadDelay = 1f;
    [SerializeField] ParticleSystem crashVFX;


    void OnCollisionEnter(Collision collision)
    {
        Debug.Log(this.name + " Collisioned with!!" + collision.gameObject.name);     
    }

    void OnTriggerEnter(Collider other)
    {
        Debug.Log($"{this.name} ** Triggered by ** {other.gameObject.name}");
        StartCrashSequence();
    }


    void StartCrashSequence()
    {
        crashVFX.Play();
        GetComponent<MeshRenderer>().enabled = false;
        GetComponent<BoxCollider>().enabled = false;
        GetComponent<PlayerController>().enabled = false;
        Invoke("ReloadLevel", loadDelay);

    }

    void ReloadLevel()
    {
        int currentScene = SceneManager.GetActiveScene().buildIndex;
        SceneManager.LoadScene(currentScene);
    }

    
}
