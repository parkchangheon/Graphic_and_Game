using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CollisionHandler : MonoBehaviour
{

    [SerializeField] float levelLoadDelay = 0.5f;
    [SerializeField] AudioClip success;
    [SerializeField] AudioClip crash;

    AudioSource audioSource;

    bool isTransitioning = false;


    private void Start()
    {
        audioSource = GetComponent<AudioSource>();

    }


    void OnCollisionEnter(Collision collision)
    {
        if (isTransitioning)
            return;
        

        switch (collision.gameObject.tag)
        {
            case "Friendly":
                Debug.Log("This is Friendly");
                break;

            case "Finish":
                StartSuccessSequence();
                break;

            case "Fuel":
                Debug.Log("You Pick Up Fuel");
                break;

            default:
                StartCrashSequence();
                break;
        }
        
    }

    private void StartSuccessSequence() //Arrive at Finish line
    {
        isTransitioning = true;
        audioSource.Stop();
        audioSource.PlayOneShot(success);
        //todo add particle effect upon crash
        GetComponent<movement>().enabled = false;
        Invoke("LoadNextLevel", levelLoadDelay);
    }


    void StartCrashSequence() // didn't arrive at finish line
    {
        isTransitioning = true;
        audioSource.Stop();
        audioSource.PlayOneShot(crash);
        //todo add particle effect upon crash
        GetComponent<movement>().enabled = false;
        Invoke("ReloadLevel", levelLoadDelay);
    }



    void LoadNextLevel()
    {
        int currentSceneIndex = SceneManager.GetActiveScene().buildIndex;
        int nextSceneIndex = currentSceneIndex + 1;
        if(nextSceneIndex == SceneManager.sceneCountInBuildSettings)
        {
            nextSceneIndex = 0;
        }
        SceneManager.LoadScene(nextSceneIndex);
    }

    void ReloadLevel()
    {
        int currentSceneIndex = SceneManager.GetActiveScene().buildIndex;
        SceneManager.LoadScene(currentSceneIndex);
    }

}
